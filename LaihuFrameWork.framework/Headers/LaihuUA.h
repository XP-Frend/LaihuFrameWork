
#import <Foundation/Foundation.h>
#import <WebRTC/RTCIceServer.h>

@class LaihuUA;
@class LaihuSession;
@class RemoteContact;

extern NSString* const ACUALoginChangedReasonConnected;
extern NSString* const ACUALoginChangedReasonDisconnected;
extern NSString* const ACUALoginChangedReasonConnectionFailed;

typedef NS_ENUM (NSUInteger, ACLogLevel) {
    ACLogLevelNone,
    ACLogLevelError,
    ACLogLevelWarn,
    ACLogLevelInfo,
    ACLogLevelVerbose
};

typedef NS_ENUM(NSInteger, ACTransportType) {
    ACTransportUndefined = -1,
    ACTransportUDP = 0,
    ACTransportTCP = 1,
    ACTransportTLS = 2 
};

typedef NSDictionary<NSString*, NSString*> SipHeadersDictionary;

#pragma mark -

@protocol ACLoggerProtocol <NSObject>
- (void) acLogMessage:(NSString*)logMsg;
@end

#pragma mark -

@protocol LaihuEventListener <NSObject>
@optional

- (void) login:(BOOL)isLogin cause:(NSString*)cause;
- (void) logout:(BOOL)isLogout cause:(NSString*)cause;
- (void) incomingCall:(LaihuSession*)call;

@end

#pragma mark -

@interface RemoteContact: NSObject
@property (nonatomic, strong) NSString *displayName;
@property (nonatomic, strong) NSString *userName;
@property (nonatomic, strong) NSString *domain;
@end

#pragma mark -

@interface LaihuUA : NSObject

@property (nonatomic, weak) id <LaihuEventListener> delegate;

// True to allow session timer to be used. False to disable it completely. Default is true.
@property (nonatomic, assign) BOOL useSessionTimer;

// Set the registration expiration interval. Default is 600 seconds.
@property (nonatomic, assign) int regExpires;

// Logger log level
@property (nonatomic, assign) ACLogLevel logLevel;

// Logger delegate
@property (nonatomic, assign) id<ACLoggerProtocol> logger;

// User Agent string to be added to outgoing SIP messages
@property (nonatomic, strong) NSString* userAgent;

@property (nonatomic, assign) BOOL mustLogin;

// Additional headers to all REGISTER requests. Must conform to RFC 3261.
@property (nonatomic, strong) SipHeadersDictionary* registerExtraHeaders;

// Additional headers to all INVITE requests / responses. Must conform to RFC 3261.
@property (nonatomic, strong) SipHeadersDictionary* inviteExtraHeaders;     

// Getter for current sessions
@property (nonatomic, readonly) NSArray <LaihuSession*>* sessions;     

// Standard Methods
+ (instancetype) getInstance;

/// 设置服务器连接信息
/// @param proxyAddress 代理服务器地址
/// @param port 代理服务器端口
/// @param serverDomain 注册服务端域名
/// @param transport SIP通讯协议-UDP/TCP/TLS
/// @param iceServer NSString ICE服务器地址
/// @param certificatePath NSString TLS 证书地址
- (void) setServerConfig:(NSString*)proxyAddress
                    port:(int)port
            serverDomain:(NSString*)serverDomain
               transport:(ACTransportType)transport
               iceServer:(NSString *)iceServer
             certificate:(NSString *)certificatePath;



/// SM$解密
/// @param content 要解密的内容
/// @param key 解密key
- (NSString *)decryptUserInfoWithContent:(NSString *)content
                                     key:(NSString *)key;

/// SM4加密
/// @param content 要加密的内容
/// @param key 加密key
- (NSString *)encryptUserInfoWithContent:(NSString *)content
                                     key:(NSString *)key;

/// 设置账号信息参数
/// @param userName 注册用户名
/// @param displayName 注册密码
/// @param password 分级显示名
/// @param authName 分机校验用户名
/// @param login 是否需要登陆
- (void) setAccount:(NSString*)userName
        displayName:(NSString*)displayName
           password:(NSString*)password
           authName:(NSString*)authName
           useLogin:(BOOL)login;

- (void) login;

- (void) logout;

/// 发起外呼呼叫
/// @param call_to 被叫方号码信息
/// @param withVideo 是否发起视频
/// @param inviteHeaders 消息自定义头字段
- (LaihuSession*) call:(RemoteContact*)call_to
                  withVideo:(BOOL)withVideo
              inviteHeaders:(SipHeadersDictionary*)inviteHeaders;


@end
