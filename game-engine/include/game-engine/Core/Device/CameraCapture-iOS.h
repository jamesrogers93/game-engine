
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface CameraCaptureIOS : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic) float camWidth;
@property (nonatomic) float camHeight;
@property (nonatomic) float padding;
//@property (nonatomic) NSArray *delegates;

- (int)initialise: (NSString *) sessionPreset;
- (void)deinitialise;

- (void)startCapture;
- (void)stopCapture;

- (void)bindTextures;

-(GLuint)getLumaTextureID;
-(GLuint)getChromaTextureID;

@end
