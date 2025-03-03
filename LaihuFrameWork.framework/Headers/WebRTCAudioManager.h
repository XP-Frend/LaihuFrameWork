
#import <Foundation/Foundation.h>
 
#pragma mark - NSNotifications

extern NSString * const ACAudioRouteChangedNotification;
extern NSString * const ACAudioRouteRouteChangedNotificationCurrentRouteKey;

extern NSString * const ACAudioRouteRouteAvailabilityChangedNotification;
extern NSString * const ACAudioRouteRouteAvailabilityChangedReceiverAvailableKey;
extern NSString * const ACAudioRouteRouteAvailabilityChangedSpeakerAvailableKey;
extern NSString * const ACAudioRouteRouteAvailabilityChangedBluetoothAvailableKey;

#pragma mark - 

typedef NSNumber AudioRouteNumber;

typedef NS_ENUM(NSUInteger, AudioRoute)
{
    AudioRouteEarpiece = 0,
    AudioRouteLoutSpeaker = 1,
    AudioRouteBluetooth = 2,
    AudioRouteUndefined = 3
};

typedef NS_OPTIONS(NSUInteger, AudioRoutingOptions)
{
    AudioRouteOptionNone = 0,
    AudioRouteOptionOverrideToLoudSpeaker = 0x1,
    AudioRouteOptionAllowBluetooth = 0x2
};

#pragma mark -

@protocol WebRTCAudioRoutesListener <NSObject>
@optional

- (void) audioRoutesChanged:(NSArray<AudioRouteNumber*>*)audioRouteList;
- (void) currentAudioRouteChanged:(AudioRoute)newAudioRoute;

@end

@interface WebRTCAudioManager : NSObject

@property (nonatomic, weak) id <WebRTCAudioRoutesListener> delegate;
@property (nonatomic, readonly) AudioRoutingOptions currentRoutingOptions;
@property (nonatomic, readonly)     BOOL             headsetDeviceAvailable;
@property (nonatomic, readonly)     BOOL             bluetoothDeviceAvailable;

+ (WebRTCAudioManager*) getInstance;
- (NSArray<AudioRouteNumber*>*) getAvailableAudioRoutes;
- (AudioRoute) getAudioRoute;
- (BOOL) setAudioRoute:(AudioRoutingOptions)options;
- (BOOL) overrideAudioRouteToSpeaker:(BOOL)enable;
- (BOOL) routeAudioToEnableBluetooth:(BOOL)enable;

@end
