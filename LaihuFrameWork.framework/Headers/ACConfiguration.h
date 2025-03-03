
#import <Foundation/Foundation.h>

extern NSInteger const LocalServerDefaultPort;

typedef NS_ENUM(NSUInteger, DTMFMethod) {  
    WEBRTC = 0,
    SIP_INFO
};

#pragma mark - 

@interface DTMFOptions : NSObject <NSCopying>

@property (nonatomic, readwrite) DTMFMethod dtmfMethod; // Defaults to WEBRTC
@property (nonatomic, readwrite) NSInteger duration;    // Duration of DTMF event in Milliseconds. Defaults to 100.
@property (nonatomic, readwrite) NSInteger intervalGap; // Milliseconds. Only relevant for WEBRTC method. Defaults to 70.

- (instancetype) initWithDtmfMethod:(DTMFMethod)method duration:(NSInteger)duration intervalGap:(NSInteger)intervalGap;

@end

#pragma mark - 

@interface VideoConfiguration : NSObject <NSCopying>
// Camera parameters
@property (nonatomic, readwrite) NSInteger cameraWidth;     // Defaults to 640 pixels
@property (nonatomic, readwrite) NSInteger cameraHeight;    // Defaults to 480 pixels
@property (nonatomic, readwrite) NSInteger cameraFrameRate; // Defaults to 15 Frames Per Second

// Rendering Views Parameters
@property (nonatomic, readwrite) float LOCAL_X_CONNECTING;
@property (nonatomic, readwrite) float LOCAL_Y_CONNECTING;
@property (nonatomic, readwrite) float LOCAL_WIDTH_CONNECTING;
@property (nonatomic, readwrite) float LOCAL_HEIGHT_CONNECTING;
@property (nonatomic, readwrite) float LOCAL_X_CONNECTED;
@property (nonatomic, readwrite) float LOCAL_Y_CONNECTED;
@property (nonatomic, readwrite) float LOCAL_WIDTH_CONNECTED;
@property (nonatomic, readwrite) float LOCAL_HEIGHT_CONNECTED;
@property (nonatomic, readwrite) float REMOTE_X;
@property (nonatomic, readwrite) float REMOTE_Y;
@property (nonatomic, readwrite) float REMOTE_WIDTH;
@property (nonatomic, readwrite) float REMOTE_HEIGHT;

- (instancetype) initWithVideoConfiguration:(VideoConfiguration*)configuration;

@end

#pragma mark - 

@interface ACConfiguration : NSObject

+ (ACConfiguration*) getConfiguration;

@property (nonatomic, readonly) NSString *version;
@property (nonatomic, readwrite) int localServerPort; // Default is LocalServerDefaultPort
@property (nonatomic, copy) DTMFOptions* dtmfOptions;
@property (nonatomic, copy) VideoConfiguration* videoConfiguration;

@end



