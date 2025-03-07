
/** @file RCDeviceDelegate.h */

#import "RCDevice.h"

@class RCDevice;
@class RCConnection;
@class RCPresenceEvent;

// map RCConnectivityStatus enum with Reachability.h:NerworkStatus enum 1-1
typedef enum : NSInteger {
    RCConnectivityStatusNone = 0,  // no restcomm connectivity either we have no internet connectivity or couldn't register to restcomm (or both)
    RCConnectivityStatusWiFi,  // restcomm reachable and online via Wifi (or if in registrarless mode we don't register with restcomm; we just know that we have internet connectivity)
    RCConnectivityStatusCellular,  // restcomm reachable and online via cellular (same as above for registraless)
} RCConnectivityStatus;

/**
 *  RCDevice notifies its delegate for RCDevice related events defined in this delegate protocol
 */
@protocol RCDeviceDelegate<NSObject>

@required
/**
 *  @abstract RCDevice stopped listening for incoming connections (**Not Implemented yet**)
 *
 *  @param device Device of interest
 *  @param error  The reason it stopped
 */
- (void)device:(RCDevice*)device didStopListeningForIncomingConnections:(NSError*)error;

/**
 *  @abstract RCDevice started listening for incoming connections
 *
 *  @param device Device of interest
 */
- (void)deviceDidStartListeningForIncomingConnections:(RCDevice*)device;

/**
 *  @abstract RCDevice received incoming connection
 *
 *  @param device     Device of interest
 *  @param connection Newly established connection
 */
- (void)device:(RCDevice*)device didReceiveIncomingConnection:(RCConnection*)connection;

/**
 *  @abstract RCDevice received incoming instant message
 *
 *  @param device  Device of interest
 *  @param message Instant message text
 *  @param params Dictionary with parameters of the incoming message
 */
- (void)device:(RCDevice *)device didReceiveIncomingMessage:(NSString *)message withParams:(NSDictionary *)params;

//@optional
/**
 *  @abstract RCDevice received presence update (**Not implemented yet**)
 *
 *  @param device        Device of interest
 *  @param presenceEvent Presence event
 */
//- (void)device:(RCDevice *)device didReceiveConnectivityUpdate:(RCConnectivityStatus)deviceState;

@optional
/**
 *  @abstract RCDevice received presence update (**Not implemented yet**)
 *
 *  @param device        Device of interest
 *  @param presenceEvent Presence event
 */
- (void)device:(RCDevice *)device didReceivePresenceUpdate:(RCPresenceEvent *)presenceEvent;

@end

