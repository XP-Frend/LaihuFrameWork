
#import <Foundation/Foundation.h>
//#import "RCDeviceDelegate.h"
#import "RCConnectionDelegate.h"


/** @file RCDevice.h */

/**
 * Device State
 */
typedef enum {
    RCDeviceStateOffline = 0,  /**< Device is offline */
	RCDeviceStateReady,  /**< Device is ready to make and receive connections */
	RCDeviceStateBusy  /**< Device is busy */
} RCDeviceState;

/**
 * Connectivity Type
 */
typedef enum {
    RCDeviceConnectivityTypeNone = 0,
    RCDeviceConnectivityTypeWifi,  /**< Device is connected via Wifi (given that RCDeviceState is Ready or Busy) */
    RCDeviceConnectivityTypeCellularData,  /**< Device is connected via Cellular Data (given that RCDeviceState is Ready or Busy) */
} RCDeviceConnectivityType;

/**
 * ICE Config Type
 */
typedef NS_ENUM(NSInteger, ICEConfigType) {
    kXirsysV2 = 0,
    kXirsysV3,
    kCustom
};


extern NSString* const RCDeviceCapabilityIncomingKey;
extern NSString* const RCDeviceCapabilityOutgoingKey;
extern NSString* const RCDeviceCapabilityExpirationKey;
extern NSString* const RCDeviceCapabilityAccountSIDKey;
extern NSString* const RCDeviceCapabilityApplicationSIDKey;
extern NSString* const RCDeviceCapabilityApplicationParametersKey;
extern NSString* const RCDeviceCapabilityClientNameKey;

extern NSString* const RCAorKey;
extern NSString* const RCPasswordKey;
extern NSString* const RCTurnEnabledKey;
extern NSString* const RCTurnUrlKey;
extern NSString* const RCTurnUsernameKey;
extern NSString* const RCTurnPasswordKey;
extern NSString* const RCIceDomainKey;
extern NSString* const RCSignalingSecureKey;
extern NSString* const RCSignalingCertificateDirKey;
extern NSString* const RCIceConfigTypeKey;
extern NSString* const RCIceServersKey;
extern NSString* const RCRegistrarKey;
extern NSString* const RCTransport;

extern NSString* const RCUsername;
extern NSString* const RCVideoEnabled;
extern NSString* const RCSipHeaders;
extern NSString* const RCMessage;


//push related
extern NSString* const RCPushFriendlyNameKey;
extern NSString* const RCRestcommAccountPasswordKey;
extern NSString* const RCRestcommAccountEmailKey;
extern NSString* const RCPushDomainKey;
extern NSString* const RCPushTokenKey;
extern NSString* const RCPushCertificatesPathPublicKey;
extern NSString* const RCPushCertificatesPathPrivateKey;
extern NSString* const RCPushIsSandbox;
extern NSString* const RCRestcommAccountPasswordKey;
extern NSString* const RCHttpDomainKey;

@class RCConnection;
@protocol SipManagerDeviceDelegate;
@protocol RCDeviceDelegate;

/**
 *  RCDevice Represents an abstraction of a communications device able to make and receive calls, send and receive messages etc. Remember that
 *  in order to be notified of RestComm Client events you need to set a delegate to RCDevice and implement the applicable methods.
 *  If you want to initiate a media connection towards another party you use [RCDevice connect:delegate:] which returns an RCConnection object representing
 *  the new outgoing connection. From then on you can act on the new connection by applying RCConnection methods on the handle you got from [RCDevice connect:delegate:].
 *  If there’s an incoming connection you will be notified by [RCDeviceDelegate device:didReceiveIncomingConnection:] delegate method. At that point you can use RCConnection methods to
 *  accept or reject the connection.
 *
 *  As far as instant messages are concerned you can send a message using [RCDevice sendMessage:] and you will be notified of an incoming message
 *  via [RCDeviceDelegate device:didReceiveIncomingMessage:withParams:] delegate method.
 */
@interface RCDevice : NSObject
/**
 *  @abstract Device state
 */
@property (nonatomic) RCDeviceState state;

/**
 *  @abstract Device connectivity type, given that RCDeviceState is Ready or Busy
 */
@property (nonatomic) RCDeviceConnectivityType connectivityType;

/**
 *  @abstract Device capabilities (**Not Implemented yet**)
 */
@property (nonatomic, readonly) NSDictionary* capabilities;

/**
 *  @abstract Delegate that will be receiving RCDevice events described at RCDeviceDelegate protocol
 */
@property (nonatomic, assign) id<RCDeviceDelegate> delegate;

/**
 *  @abstract Is sound for incoming connections enabled
 */
@property (nonatomic) BOOL incomingSoundEnabled;

/**
 *  @abstract Is sound for outgoing connections enabled
 */
@property (nonatomic) BOOL outgoingSoundEnabled;

/**
 *  @abstract Is sound for disconnect enabled (**Not Implemented yet**)
 */
@property (nonatomic) BOOL disconnectSoundEnabled;

/*
 *  Initialize a new RCDevice object with the given parameters
 *
 *  @param parameters      Parameters for the Device entity. Possible keys: <br>
 *    <b>RCAorKey</b>: identity (or address of record) for the client, like <i>'sip:ios-sdk@cloud.restcomm.com'</i> <br>
 *    <b>RCPasswordKey</b>: password for the client <br>
 *    <b>RCTurnEnabledKey</b>: should TURN be enabled? <br>
 *    <b>RCTurnUrlKey</b>: TURN url if you want to use TURN for webrtc ICE negotiation, like <i>'https://turn.provider.com/turn'</i> <br>
 *    <b>RCTurnUsernameKey</b>: TURN username <br>
 *    <b>RCTurnPasswordKey</b>: TURN password <br>
 *    <b>RCRegistrarKey</b>: Restcomm instance to use, like <i>'cloud.restcomm.com'</i>. Leave empty for registrar-less mode <br>
 *    <b>RCSignalingSecureKey</b>: Should signaling traffic be encrypted? For traffic to be encrypted the 'signaling-certificate-dir' below should be provided as well <br>
 *    <b>RCSignalingCertificateDirKey</b>: Directory where files agent.pem and cafile.pem are installed inside the App bundle needed when TLS is to be used for signaling.
      agent.pem contains the private key and certificate to be used by the signaling facilities. cafile.pem is a file containing all trusted certs
 *    <b>RCIceConfigTypeKey<b>:  Should be integer value of the following kXirsysV2 = 0, kXirsysV3 = 1 , kCustom = 2.
        kXirsysV2 and kXirsysV3 is about utilizing an ICE configuration URL using Xirsys V2 or V3 respectively. 
        kCustom is about discovering the ICE urls (i.e. STUN and TURN) in the App level and providing to the SDK directly 
            without utilizing an ICE configuration URL. This is handy if you host your own ICE servers, or want more control
 *    <b>RCIceDomainKey</b> If ice-config-type is kXirsysV3, ice-domain must be provided; for example: restcomm
 *    <b>RCIceServersKey</b> NSArray of NSDictionary data of the STUN and TURN servers; This key is mandatory if ice-config-type is 'kCustom'; Example with 2 servers:
            parameter to pass (Array):
            @[
                @{ @"url":@"URL", @"username":@"USERNAME_HERE", @"credential":@"KEY_HERE"},
                @{ @"url":@"URL" }
            ]
 
 *  @param delegate        Delegate of RCDevice
 *  @return Newly initialized RCDevice object
 */
- (id)initWithParams:(NSDictionary*)parameters delegate:(id<RCDeviceDelegate>)delegate;

/**
 *  Initialize a new RCDevice object with capability token
 *
 *  @param capabilityToken Capability Token
 *  @param delegate        Delegate of RCDevice
 *
 *  @return Newly initialized object
 */
- (id)initWithCapabilityToken:(NSString*)capabilityToken delegate:(id<RCDeviceDelegate>)delegate;

/**
 *  @abstract Start listening for incoming connections (RCDevice is configured to listen once it is instantiated)
 */
- (void)listen;

/**
 *  @abstract Stop listening for incoming connections
 */
- (void)unlistenWithNetWorkChange:(BOOL)change;

/**
 *  @abstract Update Capability Token
 *
 *  @param capabilityToken New Capability Token (**Not Implemented**)
 */
- (void)updateCapabilityToken:(NSString*)capabilityToken;

/**
 *  @abstract Retrieve RCDevice parameters
 *
 *  @return RCDevice parameters
 */
- (NSDictionary*)getParams;

/**
 *  @abstract Create an outgoing connection to an endpoint
 *
 *  @param parameters Parameters for the outgoing connection. Possible keys: <br>
 *    <b>RCUsername</b>: Who is the called number, like <i>'+1235'</i> or <i>'sip:+1235@cloud.restcomm.com'</i> <br>
 *    <b>RCVideoEnabled</b>: Whether we want WebRTC video enabled or not <br>
 *    <b>RCSipHeaders</b>: An optional NSDictionary of custom SIP headers we want to add to the INVITE <br>
 *  @param delegate   The delegate object that will receive events when the connection state changes
 *
 *  @return An RCConnection object representing the new connection
 */
- (RCConnection*)connect:(NSDictionary*)parameters delegate:(id<RCConnectionDelegate>)delegate;


/**
 *  @abstract Send a text message 
 *
 *  @param parameters  Message parameters. Possible keys are:  <br>
 *    <b>RCUsername</b>: Who is the recepient of the text message, like <i>'sip:+1235@cloud.restcomm.com'</i> <br>
 *    <b>RCMessage</b>: Content of the message <br>
 *    <b>RCSipHeaders</b>: An optional NSDictionary of custom SIP headers we want to add to the MESSAGE <br>
 *
 *  @return A boolean whether message was sent or not.
 */
- (BOOL)sendMessage:(NSDictionary*)parameters;

/**
 *  @abstract Disconnect all connections
 */
- (void)disconnectAll;

/**
 *  @abstract Update RCDevice parameters
 *
 *  @param params Dictionary of key/value pairs of the parameters that will be updated: <br>
 *    <b>RCAorKey</b>: identity (or address of record) for the client, like <i>'sip:ios-sdk@cloud.restcomm.com'</i> <br>
 *    <b>RCPasswordKey</b>: password for the client <br>
 *    <b>RCTurnEnabledKey</b>: should TURN be enabled? <br>
 *    <b>RCTurnUrlKey</b>: TURN url if you want to use TURN for webrtc ICE negotiation, like <i>'https://turn.provider.com/turn'</i> <br>
 *    <b>RCTurnUsernameKey</b>: TURN username <br>
 *    <b>RCTurnPasswordKey</b>: TURN password <br>
 *    <b>RCRegistrarKey</b>: Restcomm instance to use, like <i>'sip:cloud.restcomm.com'</i>. Leave empty for registrar-less mode <br>
 *    <b>RCSignalingSecureKey</b>: Should signaling traffic be encrypted? For traffic to be encrypted the 'signaling-certificate-dir' below should be provided as well <br>
 *    <b>RCSignalingCertificateDirKey</b>: Directory where files agent.pem and cafile.pem are installed inside the App bundle needed when TLS is to be used for signaling. agent.pem is the client/server cert containing key and certificate to be used by the signaling facilities. cafile.pem is a file containing all trusted certs
 *
 *  @return If update of parameters was successful. Typical reason to fail is connectivity issues.
 */
- (BOOL)updateParams:(NSDictionary*)params;

// To be used internally by the library -not for application usage
- (void)clearCurrentConnection;

/**
 *  Register the application for the push notifications
 * <b>RCPushFriendlyNameKey</b>: name of the client application
 * <b>RCRestcommAccountEmailKey</b> account's email
 * <b>RCRestcommAccountPasswordKey</b>: password for an account<br>
 * <b>RCPushDomainKey</b> domain for the push notifications; for example: push.restcomm.com
 * <b>RCPushTokenKey</b>: push notification token from the APN
 * <b>RCPushCertificatesPathPublicKey</b>: Path where exported APN's public certificate file is installed inside the App bundle.
 * <b>RCPushCertificatesPathPrivateKey</b>: Path where exported APN's private RSA certificate file is installed inside the App bundle.
 * The certificates are needed in order to receive push notifications. The server is using them to send the push notification to device.
 * NOTE:
 * By default APNS provides to developer '.p12' SSL certificate. Restcomm Push Notification Server requires a couple of modifications with this file.
 * Generate '.pem' certificate:
 *      openssl pkcs12 -in /path/to/cert.p12 -nokeys -out /path/to/cert.pem -nodes
 * Generate '.pem' private key:
 *      openssl pkcs12 -in /path/to/cert.p12 -nocerts -out /path/to/key.pem -nodes
 * Format '.pem' private key to pkcs8:
 *      openssl pkcs8 -topk8 -inform pem -in /path/to/key(pkcs12).pem -outform pem -nocrypt -out /path/to/key(pkcs8).pem
 *
 * <b>RCPushIsSandbox</b>: BOOL presented with number ([NSNumber numberWithBool:YES/NO]); It should be true if voip push certifictes are for development version of the
 * application, if its production it should be set to NO.
 * <b>RCHttpDomainKey</b>: Restcomm HTTP domain, like 'cloud.restcomm.com'
 *
 * @param delegate The delegate object that will receive events when registering for push (success, error)
 */
//- (void)registerPushToken:(NSDictionary*)parameters delegate:(id<RCRegisterPushDelegate>)delegate;

/* DEBUG:
-(void)startSofia;
-(void)stopSofia;
 */

@end

