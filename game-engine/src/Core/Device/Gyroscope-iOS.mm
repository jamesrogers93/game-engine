
// Game Engine Device
#import "game-engine/Core/Device/Gyroscope-iOS.h"
#import "game-engine/Core/Device/Gyroscope.h"

// STD
#import <iostream>

// GLM
#import <glm/gtc/matrix_transform.hpp>
#import <glm/gtx/quaternion.hpp>

// Kudan CV
#import "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/ar-fighter/ar-fighter-ios/ARFighter/KudanCV/KudanCV.h"

@implementation GyroscopeIOS

void Gyroscope::initialise()
{
    self = [[GyroscopeIOS alloc] init];

    [(id)self initialise];
}

glm::dquat Gyroscope::getOrientation()
{
    return [(id)self getGyroOrientation];
}

- (void)initialise
{
    
    if (!_motionManager)
    {
        _motionManager = [[CMMotionManager alloc] init];
        _motionManager.gyroUpdateInterval = 0.05;
    }
    
    CMAttitudeReferenceFrame gyroReferenceFrame = CMAttitudeReferenceFrameXArbitraryCorrectedZVertical;
    
    CMDeviceMotion *deviceMotion = _motionManager.deviceMotion;
    
    self.referenceAttitude = deviceMotion.attitude;
    [_motionManager startDeviceMotionUpdatesUsingReferenceFrame:gyroReferenceFrame];
}


- (void)deinitialise
{
    [_motionManager stopDeviceMotionUpdates];
    
    _motionManager = nil;

    [(id)self dealloc];
}

KudanQuaternion matrixToQuaternion(KudanMatrix3 matrix)
{
    // convert the matrix to a quaternion:
    float w = sqrt(1.0 + matrix(0, 0) + matrix(1, 1) + matrix(2, 2)) / 2.0;
    float w4 = (4.0 * w);
    float x = (matrix(1, 2) - matrix(2, 1)) / w4;
    float y = (matrix(2, 0) - matrix(0, 2)) / w4;
    float z = (matrix(0, 1) - matrix(1, 0)) / w4;
    
    return KudanQuaternion(-x, y, -z, w);
}

KudanMatrix3 getRotationMatrixZ(double angle)
{
    double sinr = sin(angle);
    double cosr = cos(angle);
    
    KudanMatrix3 R;
    R(0,0) = cosr;
    R(0,1) = -sinr;
    R(0,2) = 0;
    
    R(1,0) = sinr;
    R(1,1) = cosr;
    R(1,2) = 0;
    
    R(2,0) = 0;
    R(2,1) = 0;
    R(2,2) = 1;
    
    return R;
}

KudanMatrix3 multiply(KudanMatrix3 B, KudanMatrix3 A)
{
    KudanMatrix3 C;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            // dot product of row i of A and col j of B
            for (int k = 0; k < 3; k++) {
                C(i,j) += A(i,k)*B(k,j);
            }
        }
    }
    return C;
}

glm::mat4 rotateMatrix(glm::mat4 m, float a, glm::vec3 axis)
{
    return glm::rotate(m, a, axis);
}


- (glm::dquat)getGyroOrientation
{
    if (_motionManager.deviceMotion == nil)
    {
        return glm::dquat();
        //return KudanQuaternion();
    }
    
    CMAttitude *attitude = _motionManager.deviceMotion.attitude;
    CMRotationMatrix rot = attitude.rotationMatrix;
    
    glm::mat4 glmMatrix;
    glmMatrix[0][0] = rot.m11;
    glmMatrix[0][1] = rot.m21;
    glmMatrix[0][2] = rot.m31;
    glmMatrix[1][0] = rot.m12;
    glmMatrix[1][1] = rot.m22;
    glmMatrix[1][2] = rot.m32;
    glmMatrix[2][0] = rot.m13;
    glmMatrix[2][1] = rot.m23;
    glmMatrix[2][2] = rot.m33;
    
    // THIS WORKING WHEN JUST GYROSCOPE
    //glm::fquat test = glm::normalize(glm::quat_cast(glmMatrix));
    glm::fquat test = glm::quat_cast(glmMatrix);
    glm::fquat test2 = glm::fquat(test.w, -test.y, test.x, test.z);
    
    // Rotate by 90 degrees on x axis so that z no longer points down
    glm::fquat q = glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0,0.0,0.0));
    return test2 * q;
    // END WORKING
    
    /*glm::fquat test = glm::quat_cast(glmMatrix);
    //glm::fquat test2 = glm::fquat(test.w, test.x, test.y, test.z);
    
    // Rotate by 90 degrees on z axis so that GL axis line with gyroscpe axis
    glm::fquat q = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
    
    // Now rotate around x axis so that the z axis is horizontal
    glm::fquat q1 = glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0,0.0,0.0));
    
    return q1 * q * test;*/

}


@end
