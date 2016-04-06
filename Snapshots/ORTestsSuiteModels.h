#import <Foundation/Foundation.h>

@class ORTestCase, ORKaleidoscopeCommand, ORSnapshotCreationReference;

NS_ASSUME_NONNULL_BEGIN

@interface ORTestSuite : NSObject
@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSMutableArray *testCases;

- (NSArray *)failingTestCases;
- (BOOL)hasFailingTests;
- (BOOL)hasNewSnapshots;

+ (ORTestSuite *)suiteFromString:(NSString *)line;
- (ORTestCase *)latestTestCase;
@end

@interface ORTestCase : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSMutableArray *commands;
@property (nonatomic, strong) NSMutableArray *snapshots;

- (NSArray *)uniqueDiffCommands;

@property (nonatomic, assign) BOOL hasFailingTests;

+ (ORTestCase *)caseFromString:(NSString *)line;
- (void)addCommand:(ORKaleidoscopeCommand *)command;
- (void)addSnapshot:(ORSnapshotCreationReference *)snapshot;
- (ORKaleidoscopeCommand *)latestCommand;
@end


@interface ORKaleidoscopeCommand : NSObject

- (void)launch;
- (void)swapImages;
- (void)openInFinder;
- (void)openInPreview;

@property (nonatomic, assign) BOOL fails;
@property (nonatomic, copy) NSString *beforePath;
@property (nonatomic, copy) NSString *afterPath;
@property (nonatomic, copy) NSString *fullCommand;
@property (nonatomic, weak) ORTestCase *testCase;
@property (nonatomic, copy) NSString *projectLocation;


+ (instancetype)commandFromString:(NSString *)command;
@end

@interface ORSnapshotCreationReference : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, weak) ORTestCase *testCase;

+ (instancetype)referenceFromString:(NSString *)line;
@end

NS_ASSUME_NONNULL_END