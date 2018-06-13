#import <Foundation/Foundation.h>

@class SecureContentReference;

@interface SecureInputStream : NSInputStream <NSStreamDelegate>

/**
 Initialize the SecureInputStream by providing an NSInputStream from which
 to read cleartext data and a SecurityContentReference to provide the scheme,
 key material, and other metadata needed to encrypt the data.
 
 \param stream An "upstream" NSInputStream from which cleartext data is read.
 \param scr    The SecureContentReference that references the data to be 
               encrypted with given NSInputStream.
 \returns      The initialized SecureInputStream.
 */
- (instancetype)initWithStream:(NSInputStream *)stream
                           scr:(SecureContentReference *)scr
                         error:(NSError **)error;

/**
 The SecureInputStream implements the NSStreamDelegate protocol whereby it
 listens for events from the "upstream" NSInputStream.  A component that 
 consumes NSInputStream may then similarly act as a delegate of the
 SecureInputStream itself and receive streaming events.  Most events
 generated by the "upstream" NSInputStream are simply forwarded through to the
 delegate of the SecureInputStream.  Clients of the SecureInputStream
 class should not invoke this method directly.
 
 \param stream    The stream from which event messages are originating.
 \param eventCode A code describing the type of stream event.
 */
- (void)stream:(NSStream *)stream handleEvent:(NSStreamEvent)eventCode;

/**
 The standard NSString read message.  The client application may invoke this
 from within its own delegate event handling code in order to receive encrypted
 stream data.
 
 \param buffer    The buffer to which encrypted data will be written.
 \param requested The maximum number of bytes that receiver should write.
 \returns         The number of bytes actually read, or -1 if an error occurred.
 */
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)requested;

/**
 Returns the number of bytes currently available for reading from the stream.
 */
- (BOOL)hasBytesAvailable;

/**
 Close the stream.  Will also close the "upstream" NSInputStream.
 */
- (void)close;

/**
 The following are standard API methods of an NSStream.  The implementation
 for each of these is essentially a proxy to the contained NSInputStream 
 provided in the initWithStream.
 */
- (id<NSStreamDelegate>)delegate;
- (void)setDelegate:(id<NSStreamDelegate>)delegate;
- (void)open;
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (id)propertyForKey:(NSString *)key;
- (BOOL)setProperty:(id)property forKey:(NSString *)key;
- (NSStreamStatus)streamStatus;
- (NSError *)streamError;

@end
