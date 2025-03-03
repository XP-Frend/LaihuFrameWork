
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebRTC/RTCVideoTrack.h>
#import <AVFoundation/AVFoundation.h>
#import <WebRTC/RTCCameraVideoCapturer.h>

/** @file RCConnectionDelegate.h */

@class RCConnection;

/**
 *  RCConnection notifies its delegate for connection related events defined in this delegate protocol
 */
@protocol RCConnectionDelegate<NSObject>

@required
/**
 *  @abstract Emitted when a connection failed and got disconnected
 *
 *  @param connection Connection that failed
 *  @param error      Description of the error of the Connection
 */
- (void)connection:(RCConnection*)connection didFailWithError:(NSError*)error;

/**
 *  @abstract Emitted when an RCConnection start to connect
 *
 *  @param connection Connection of interest
 */
- (void)connectionDidStartConnecting:(RCConnection*)connection;

/**
 *  @abstract Connection is established
 *
 *  @param connection Connection of interest
 */
- (void)connectionDidConnect:(RCConnection*)connection;

/**
 *  @abstract Incoming connection was cancelled
 *
 *  @param connection Connection of interest
 */
- (void)connectionDidCancel:(RCConnection*)connection;

/**
 *  @abstract Connection was declined from the remote party
 *
 *  @param connection Connection of interest
 */
- (void)connectionDidGetDeclined:(RCConnection*)connection;

- (void)connectionDidRejecte:(RCConnection *)connection;

/**
 *  @abstract Connection was disconnected
 *
 *  @param connection Connection of interest
 */
- (void)connectionDidDisconnect:(RCConnection*)connection;

- (void)connectionDidDisconnectFiald:(RCConnection*)connection;

- (void)connectionDidDisconnectHangUp:(RCConnection*)connection;

/**
 *  @abstract Received local video track for the connection. To see the video it must be rendered inside a suitable view
 *
 *  @param connection Connection of interest
 *  @param localVideoTrack Local video track
 */
- (void)connection:(RCConnection *)connection didReceiveLocalVideo:(RTCVideoTrack *)localVideoTrack;

- (void)connection:(RCConnection *)connection didSetCaptureSession:(AVCaptureSession *)captureSession;

- (void)connection:(RCConnection *)connection didCreateLocalCapturer:(RTCCameraVideoCapturer *)capturer;

- (void)connectionSipManagerCannotGetAudioOrVideoJurisdiction:(NSString *)mediaType;

/**
 *  @abstract Received remote video track for the connection. To see the video it must be rendered inside a suitable view
 *
 *  @param connection Connection of interest
 *  @param remoteVideoTrack Remote video track
 */
- (void)connection:(RCConnection *)connection didReceiveRemoteVideo:(RTCVideoTrack *)remoteVideoTrack;

@end
