

#import <Foundation/Foundation.h>
#import "LaihuUA.h"
#import "RestCommClient.h"
#import "WebRTC/RTCEAGLVideoView.h"
#import "WebRTC/RTCCameraPreviewView.h"
#import "ARDCaptureController.h"

//@import UIKit;

#pragma mark - NSNotifications


extern NSString* const ACSessionCallProgressNotification;
extern NSString* const ACSessionCallTerminatedNotification;
extern NSString* const ACSessionCameraSwitchedNotification;

// Value: NSNumber indicating a boolean value for true (front camera) or false (back camera)
extern NSString* const ACSessionCameraSwitchedFrontCameraUserInfoKey;

#pragma mark -


typedef void(^ACTaskCompletion)(void);

typedef NS_ENUM(NSUInteger, CallState) {
    ACCallStateUndefined,
    ACCallStateCalling,
    ACCallStateRinging,
    ACCallStateConnected  // Will be used for media state change. Upon onCallProgress with this value, check the "isLocalHold", "isRemoteHold" properties.
};

typedef NS_ENUM(NSUInteger, CallConnectState) {
    CallConnectStateGood = 0,      //优（音频清晰，延迟极低 丢包率10%，延时500ms 以内）
    CallConnectStateBad,           //一般（清晰度一般，延迟小 丢包率10% - 20%，延时500ms - 1000ms ）
    CallConnectStatePoor           //差（清晰度较差，延迟大 丢包率20%，延时1000ms以上）
};

typedef NS_ENUM(NSUInteger, CallTermination) {
    ACCallTerminationUndefined,
    ACCallTerminationTerminatedLocally,
    ACCallTerminationTerminatedRemotely,
    ACCallTerminationNetWorkChange,
    ACCallTerminationRejected,
    ACCallTerminationTimedOut,
    ACCallTerminationSystemCall,
    ACCallTerminationFailed
};

typedef NS_ENUM(NSUInteger, DTMF) {
    DTMF_0 = '0',
    DTMF_1 = '1',
    DTMF_2 = '2',
    DTMF_3 = '3',
    DTMF_4 = '4',
    DTMF_5 = '5',
    DTMF_6 = '6',
    DTMF_7 = '7',
    DTMF_8 = '8',
    DTMF_9 = '9',
    DTMF_ASTERISK = '*',
    DTMF_POUND = '#'
};


#pragma mark -

@class LaihuSession;

@protocol LaihuSessionEventListener <NSObject>

@optional
- (void) callProgress:(LaihuSession*)call;
- (void) callTerminated:(LaihuSession*)call;
- (void) cameraSwitched:(BOOL)frontCamera;
- (void) callChangeConnectState:(CallConnectState)state;
- (void) LaihuSessionCannotGetAudioOrVideo:(NSString *)mediaType;
@end

#pragma mark -

@interface LaihuSession : NSObject<RCConnectionDelegate>

@property (nonatomic, weak) id<LaihuSessionEventListener>                   delegate;
@property (nonatomic, readwrite) int                                        sessionID;
@property (nonatomic, assign, getter=isAudioMuted) BOOL                     muteAudio;
@property (nonatomic, assign, getter=isVideoMuted) BOOL                     muteVideo;
@property (nonatomic, readwrite) BOOL                                       isOutgoing;
@property (nonatomic, readwrite) BOOL                                       hasVideo;
@property (nonatomic, readonly) BOOL                                        isLocalHold;
@property (nonatomic, readonly) BOOL                                        isRemoteHold;
@property (nonatomic, readwrite) CallState                                  callState;
@property (nonatomic, readonly) NSInteger                                   duration;
@property (nonatomic, readonly) NSInteger                                   callStartTime;
@property (nonatomic, readwrite) RemoteContact                              *remoteNumber;
@property (nonatomic, readwrite) CallTermination                            termination;
@property (nonatomic, strong) id                                            userData;
@property (nonatomic, retain) RCConnection                                  *connection;
@property (nonatomic, readwrite) RTCVideoTrack                              *localVideoTrack;
@property (nonatomic, readwrite) RTCVideoTrack                              *remoteVideoTrack;
@property (nonatomic, assign) BOOL                                          isCallHold;

@property (nonatomic, readwrite) UIView                                     *localView;
@property (nonatomic, readwrite) UIView                                     *remoteView;

@property (nonatomic, readwrite) RTCCameraPreviewView                       *localRTCView;
@property (nonatomic, readwrite) RTCEAGLVideoView                           *remoteRTCView;

@property (nonatomic, readwrite) ARDCaptureController                       *_captureController;

/// 接听电话
/// @param headers <#headers description#>
- (void) answer:(SipHeadersDictionary*)headers;

/// 挂断电话
/// @param headers <#headers description#>
- (void) reject:(SipHeadersDictionary*)headers;

- (void) terminate;

- (void) terminateWithIndex:(NSInteger)index;

- (void) sendDtmf:(DTMF)dtmf WithType:(SendDTMFType)type;

/// 等待
/// @param hold <#hold description#>
- (void) hold:(BOOL)hold;

/// 获取当前CallId
- (NSString *)getCallId;


/// 选择摄像头
- (void) switchCamera;

/// 视频流展示
/// @param localView 当前用户
/// @param remoteView 其他用户
/// @param completion <#completion description#>
- (void) showVideoLocalView:(UIView*)localView remoteView:(UIView*)remoteView completion:(ACTaskCompletion)completion;
- (void) stopVideo; // Stop capturing and remove remote and local renderers.
- (void) showVideo:(UIViewController*)viewController;   // Currently not supported
- (void) setLocalRendererPosition_xPercentage:(float)xPercentage yPercentage:(float)yPercentage;    // Currently not supported

@end

