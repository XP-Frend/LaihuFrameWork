

#import <Foundation/Foundation.h>

@interface RCPresenceEvent : NSObject

@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly, getter = isAvailable) BOOL available;

@end
