
#import "game-engine/Core/Modules/AR/CameraCapture-iOS.h"
#import "game-engine/Core/Modules/AR/CameraCaptureInterface-iOS.h"

#import "game-engine/Core/Modules/Graphics/Context-iOS.h"

#import "game-engine/Core/Engine/System.h"

@interface CameraCaptureConcrete()
{
    AVCaptureSession *_captureSession;
    AVCaptureDevice *_device;
    dispatch_queue_t _backgroundqueue;
    BOOL finished;
    
    // OpenGL texture stuff
    CVOpenGLESTextureCacheRef _videoTextureCache;
    CVOpenGLESTextureRef _lumaTexture;
    CVOpenGLESTextureRef _chromaTexture;
}

@end

@implementation CameraCaptureConcrete

CameraCapture::CameraCapture(void)
{
    self = [[CameraCaptureConcrete alloc] init];
}

CameraCapture::~CameraCapture(void)
{
    [(id)self dealloc];
}

int CameraCapture::initialise(const CameraFace &face)
{
    bool status = [(id)self initialise];
    
    this->cameraWidth = [(id)self camWidth];
    this->cameraHeight = [(id)self camHeight];
    unsigned int screenWidth = System::screenWidth;
    unsigned int screenHeight = System::screenHeight;
    
    // Check if aspect ratio of camera image is different from screen
    float cameraAspectRatio = (float)cameraWidth / (float)cameraHeight;
    float screenAspectRatio = (float)screenWidth / (float)screenHeight;
    if( cameraAspectRatio != screenAspectRatio)
    {
        
        // Scale camera so that it's entire image fits the screen
        float heightScale = (float)screenHeight / (float)cameraHeight;
        float widthScale = (float)screenWidth / (float)cameraWidth;
        
        float w = 1.0, h = 1.0;
        if(widthScale < heightScale)
        {
            float width = (float)cameraWidth * heightScale;
            w = width / (float)screenWidth;
        }
        else
        {
            float height = (float)cameraHeight * widthScale;
            h = height / (float)screenHeight;
        }
        
        this->scale = glm::scale(glm::mat4(), glm::vec3(w, h, 1.0));
    }
    
    return status;
}

void CameraCapture::deinitialise(void)
{
    [(id)self deinitialise];
}

void CameraCapture::startCapture(void)
{
    [(id)self startCapture];
}

void CameraCapture::stopCapture(void)
{
    [(id)self stopCapture];
}

void CameraCapture::bindTextures(void)
{
    [(id)self bindTextures];
}

GLuint CameraCapture::getLumaTextureID(void)
{
    return [(id)self getLumaTextureID];
}

GLuint CameraCapture::getChromaTextureID(void)
{
     return [(id)self getChromaTextureID];
}

- (void)bindTextures
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(CVOpenGLESTextureGetTarget(_lumaTexture), CVOpenGLESTextureGetName(_lumaTexture));
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(CVOpenGLESTextureGetTarget(_chromaTexture), CVOpenGLESTextureGetName(_chromaTexture));
}

-(GLuint)getLumaTextureID
{
    return CVOpenGLESTextureGetName(_lumaTexture);
}

-(GLuint)getChromaTextureID
{
    return CVOpenGLESTextureGetName(_chromaTexture);
}

-(int)initialise
{
    //-- Create CVOpenGLESTextureCacheRef for optimal CVImageBufferRef to GLES texture conversion.
    #if COREVIDEO_USE_EAGLCONTEXT_CLASS_IN_API
        CVReturn err = CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL, [ContextiOS currentContext], NULL, &_videoTextureCache);
    #else
        CVReturn err = CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL, (__bridge void *)[ContextiOS currentContext], NULL, &_videoTextureCache);
    #endif
    
    if (err)
    {
        NSLog(@"Error at CVOpenGLESTextureCacheCreate %d", err);
        return false;
    }
    
    _captureSession = [[AVCaptureSession alloc] init];
    AVCaptureDevice *device = nil;
    NSError *error = nil;
    
    for (AVCaptureDevice *dev in [AVCaptureDevice devices])
    {
        // Discard non-cameras.
        if ([dev hasMediaType:AVMediaTypeVideo] == NO)
        {
            continue;
        }
        if (dev.position == AVCaptureDevicePositionBack)
        {
            device = dev;
            break;
        }
    }
    
    if (device == nil) {
        NSLog(@"error: couldn't find suitable camera.");
        return false;
    }
    
    _device = device;
    
    // Set continuous autofocus.
    AVCaptureFocusMode focusMode = AVCaptureFocusModeContinuousAutoFocus;
    
    if ([device isFocusModeSupported:focusMode])
    {
        [device lockForConfiguration:&error];
        [device setFocusMode:focusMode];
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"warning: continuous autofocus not supported.");
    }
    
    AVCaptureDeviceInput *deviceInput = [[AVCaptureDeviceInput alloc] initWithDevice:device error:&error];
    if (deviceInput == nil)
    {
        NSLog(@"error initialising device input: %@", error);
        return false;
    }
    
    AVCaptureVideoDataOutput *dataOutput = [[AVCaptureVideoDataOutput alloc] init];
    dataOutput.alwaysDiscardsLateVideoFrames = YES;
    
    NSMutableDictionary *videoSettings = [[NSMutableDictionary alloc] init];
    videoSettings[(NSString *)kCVPixelBufferPixelFormatTypeKey] = [NSNumber numberWithInt:kCVPixelFormatType_420YpCbCr8BiPlanarFullRange];
    dataOutput.videoSettings = videoSettings;
    
    //_backgroundqueue = dispatch_queue_create("bgqueue", NULL);
    //[dataOutput setSampleBufferDelegate:self queue:_backgroundqueue];
    [dataOutput setSampleBufferDelegate:self  queue:dispatch_get_main_queue()];
    
    [_captureSession addInput:deviceInput];
    [_captureSession addOutput:dataOutput];
    
    //_captureSession.sessionPreset = AVCaptureSessionPreset640x480;
    _captureSession.sessionPreset = AVCaptureSessionPreset1920x1080;
    
    //_camWidth = 640;
    //_camHeight = 480;
    _camWidth = 1920;
    _camHeight = 1080;
    //_delegates = [NSArray new];
    
    return true;
}

-(void)deinitialise
{
    _captureSession = nil;
    [self cleanUpTextures];
    CFRelease(_videoTextureCache);
}

-(void)startCapture
{
    [_captureSession startRunning];
}

-(void)stopCapture
{
     [_captureSession stopRunning];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{

    CVReturn err;
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    _camWidth = CVPixelBufferGetWidth(pixelBuffer);
    _camHeight = CVPixelBufferGetHeight(pixelBuffer);
    
    // Do something with data
    if (!_videoTextureCache)
    {
        NSLog(@"No video texture cache");
        return;
    }
    
    [self cleanUpTextures];
    
    // Y-plane
    glActiveTexture(GL_TEXTURE0);
    err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                       _videoTextureCache,
                                                       pixelBuffer,
                                                       NULL,
                                                       GL_TEXTURE_2D,
                                                       GL_LUMINANCE,
                                                       _camWidth,
                                                       _camHeight,
                                                       GL_LUMINANCE,
                                                       GL_UNSIGNED_BYTE,
                                                       0,
                                                       &_lumaTexture);
    if (err)
    {
        NSLog(@"Error at CVOpenGLESTextureCacheCreateTextureFromImage %d", err);
    }
    
    glBindTexture(CVOpenGLESTextureGetTarget(_lumaTexture), CVOpenGLESTextureGetName(_lumaTexture));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // UV-plane
    glActiveTexture(GL_TEXTURE1);
    err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                       _videoTextureCache,
                                                       pixelBuffer,
                                                       NULL,
                                                       GL_TEXTURE_2D,
                                                       GL_LUMINANCE_ALPHA,
                                                       _camWidth/2,
                                                       _camHeight/2,
                                                       GL_LUMINANCE_ALPHA,
                                                       GL_UNSIGNED_BYTE,
                                                       1,
                                                       &_chromaTexture);
    if (err)
    {
        NSLog(@"Error at CVOpenGLESTextureCacheCreateTextureFromImage %d", err);
    }
    
    glBindTexture(CVOpenGLESTextureGetTarget(_chromaTexture), CVOpenGLESTextureGetName(_chromaTexture));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    /*CVReturn err;
    finished = NO;
    
    CFRetain(sampleBuffer);
    
    
    double timeStamp = CMTimeGetSeconds(CMSampleBufferGetPresentationTimeStamp(sampleBuffer));
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CFRetain(imageBuffer);
    CVPixelBufferRef pixBuffer = imageBuffer;
    
    _width = CVPixelBufferGetWidth(pixBuffer);
    _height = CVPixelBufferGetHeight(pixBuffer);
    
    
    CVReturn lockResult = CVPixelBufferLockBaseAddress(pixBuffer, 0);
    if (lockResult == kCVReturnSuccess) {
        
        void *ypBuffer = CVPixelBufferGetBaseAddressOfPlane(pixBuffer, 0);
        void *cbCrBuffer = CVPixelBufferGetBaseAddressOfPlane(pixBuffer, 1);
        
        _padding = CVPixelBufferGetBytesPerRowOfPlane(pixBuffer, 0) - _width;
        
        // Wrap data buffer in NSData.
        NSData *ypData =        [NSData dataWithBytesNoCopy:ypBuffer length:CVPixelBufferGetDataSize(pixBuffer) freeWhenDone:NO];
        NSData *cbCrData =      [NSData dataWithBytesNoCopy:cbCrBuffer length:CVPixelBufferGetDataSize(pixBuffer) freeWhenDone:NO];
        
     
        // Do something with data
        if (!_videoTextureCache)
        {
            NSLog(@"No video texture cache");
            return;
        }
        
        [self cleanUpTextures];
        
        // Y-plane
        glActiveTexture(GL_TEXTURE0);
        err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                           _videoTextureCache,
                                                           imageBuffer,
                                                           NULL,
                                                           GL_TEXTURE_2D,
                                                           GL_LUMINANCE,
                                                           _width,
                                                           _height,
                                                           GL_LUMINANCE,
                                                           GL_UNSIGNED_BYTE,
                                                           0,
                                                           &_lumaTexture);
        if (err)
        {
            NSLog(@"Error at CVOpenGLESTextureCacheCreateTextureFromImage %d", err);
        }
        
        glBindTexture(CVOpenGLESTextureGetTarget(_lumaTexture), CVOpenGLESTextureGetName(_lumaTexture));
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        // UV-plane
        glActiveTexture(GL_TEXTURE1);
        err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                           _videoTextureCache,
                                                           imageBuffer,
                                                           NULL,
                                                           GL_TEXTURE_2D,
                                                           GL_LUMINANCE_ALPHA,
                                                           _width/2,
                                                           _height/2,
                                                           GL_LUMINANCE_ALPHA,
                                                           GL_UNSIGNED_BYTE,
                                                           1,
                                                           &_chromaTexture);
        if (err)
        {
            NSLog(@"Error at CVOpenGLESTextureCacheCreateTextureFromImage %d", err);
        }
        
        glBindTexture(CVOpenGLESTextureGetTarget(_chromaTexture), CVOpenGLESTextureGetName(_chromaTexture));
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        // Release data.
        ypData = nil;
        cbCrData = nil;
    }
    
    CVPixelBufferUnlockBaseAddress(pixBuffer, 0);
    
    CFRelease(imageBuffer);
    CFRelease(sampleBuffer);
    finished = YES;*/
}

- (void)cleanUpTextures
{
    if (_lumaTexture)
    {
        CFRelease(_lumaTexture);
        _lumaTexture = NULL;
    }
    
    if (_chromaTexture)
    {
        CFRelease(_chromaTexture);
        _chromaTexture = NULL;
    }
    
    // Periodic texture cache flush every frame
    CVOpenGLESTextureCacheFlush(_videoTextureCache, 0);
}

@end
