#ifndef _GYROSCOPE_IOS_H
#define _GYROSCOPE_IOS_H

#import <Foundation/Foundation.h>
#import <CoreMotion/CoreMotion.h>

class KudanQuaternion;

@interface GyroscopeIOS : NSObject

@property (nonatomic, readonly) CMMotionManager *motionManager;
@property (nonatomic) CMAttitude *referenceAttitude;
@property (nonatomic) NSMutableArray *delegates;

- (void)initialise;

//- (KudanQuaternion)getOrientation;

@end

#endif /* _GYROSCOPE_IOS_H */
