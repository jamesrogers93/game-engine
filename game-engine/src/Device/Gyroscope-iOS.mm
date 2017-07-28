
// Game Engine Device
#import "game-engine/Device/Gyroscope-iOS.h"
#import "game-engine/Device/Gyroscope.h"

// STD
#import <iostream>

// GLM
#import <glm/gtc/matrix_transform.hpp>
#import <glm/gtx/quaternion.hpp>

// Kudan CV
#import <KudanCV/KudanCV.h>

@implementation GyroscopeIOS

void Gyroscope::initialise()
{
    self = [[GyroscopeIOS alloc] init];

    [(id)self initialise];
}

glm::dquat Gyroscope::getOrientation()
{
    if(self == NULL)
    {
        std::cout << "Gyroscrope not initialised" << std::endl;
        return glm::dquat();
    }
    
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
    }
    
    CMAttitude *attitude = _motionManager.deviceMotion.attitude;
    CMRotationMatrix rot = attitude.rotationMatrix;
    
    glm::mat4 matrix;
    matrix[0][0] = rot.m11;
    matrix[0][1] = rot.m21;
    matrix[0][2] = rot.m31;
    matrix[1][0] = rot.m12;
    matrix[1][1] = rot.m22;
    matrix[1][2] = rot.m32;
    matrix[2][0] = rot.m13;
    matrix[2][1] = rot.m23;
    matrix[2][2] = rot.m33;
    
    // Cast matrix to quaternion
    glm::fquat quat = glm::quat_cast(matrix);
    
    // Flip y and switch y and x axis.
    quat = glm::fquat(quat.w, -quat.y, quat.x, quat.z);
    
    // Rotate by 90 degrees on x axis so that z no longer points down
    glm::fquat q = glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0,0.0,0.0));
    
    return quat * q;

}


@end
