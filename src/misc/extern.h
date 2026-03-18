#import <ApplicationServices/ApplicationServices.h>

#pragma mark - Callback Types

#define CONNECTION_CALLBACK(name) void name(uint32_t type, void *data, size_t data_length, void *context, int cid)
typedef CONNECTION_CALLBACK(connection_callback);

#pragma mark - Core Connection / Ports

static mach_port_t (*CGSGetConnectionPortById)(int);
extern mach_port_t mig_get_special_reply_port(void);

extern int SLSMainConnectionID(void);
extern CGError SLSNewConnection(int zero, int *cid);
extern CGError SLSReleaseConnection(int cid);
extern CGError SLSRegisterConnectionNotifyProc(int cid, connection_callback *handler, uint32_t event, void *context);

#pragma mark - Accessibility / AX

extern AXUIElementRef _AXUIElementCreateWithRemoteToken(CFDataRef data);
extern AXError _AXUIElementGetWindow(AXUIElementRef ref, uint32_t *wid);

#pragma mark - Window Queries / Properties

extern CGError SLSGetWindowBounds(int cid, uint32_t wid, CGRect *frame);
extern CGError SLSGetWindowLevel(int cid, uint32_t wid, int *level);
extern int SLSGetWindowSubLevel(int cid, uint32_t wid);
extern CGError SLSGetWindowAlpha(int cid, uint32_t wid, float *alpha);
extern CGError SLSCopyWindowProperty(int cid, uint32_t wid, CFStringRef property, CFTypeRef *value);
extern CGError SLSGetWindowOwner(int cid, uint32_t wid, int *wcid);

#pragma mark - Window Modification

extern CGError SLSSetWindowAlpha(int cid, uint32_t wid, float alpha);
extern CGError SLSSetWindowLevel(int cid, uint32_t wid, int level);
extern CGError SLSSetWindowSubLevel(int cid, uint32_t wid, int sub_level);
extern CGError SLSSetWindowOpacity(int cid, uint32_t wid, bool opaque);
extern CGError SLSSetWindowTransform(int cid, uint32_t wid, CGAffineTransform t);
extern CGError SLSGetWindowTransform(int cid, uint32_t wid, CGAffineTransform *t);
extern CGError SLSMoveWindow(int cid, uint32_t wid, CGPoint *point);
extern OSStatus SLSMoveWindowWithGroup(int cid, uint32_t wid, CGPoint *point);
extern CGError SLSSetWindowResolution(int cid, uint32_t wid, double resolution);


#pragma mark - Window Creation / Destruction

extern CGError SLSNewWindow(int cid, int type, float x, float y, CFTypeRef region, uint32_t *wid);
extern CGError SLSNewWindowWithOpaqueShapeAndContext(
    int cid, int type, CFTypeRef region, CFTypeRef opaque_shape,
    int options, uint64_t *tags, float x, float y,
    int tag_size, uint32_t *wid, void *context
);
extern CGError SLSReleaseWindow(int cid, uint32_t wid);

#pragma mark - Window Ordering / Visibility

extern CGError SLSOrderWindow(int cid, uint32_t wid, int mode, uint32_t rel_wid);
extern CGError SLSWindowIsOrderedIn(int cid, uint32_t wid, uint8_t *value);

#pragma mark - Window Tags / Shape / Effects

extern CGError SLSSetWindowTags(int cid, uint32_t wid, uint64_t *tags, size_t tag_size);
extern CGError SLSClearWindowTags(int cid, uint32_t wid, uint64_t *tags, size_t tag_size);
extern CGError SLSSetWindowShape(int cid, uint32_t wid, float x_offset, float y_offset, CFTypeRef shape);
extern CGError SLSSetWindowBackgroundBlurRadiusStyle(int cid, uint32_t wid, int radius, int style);
extern CGError SLSWindowSetShadowProperties(uint32_t wid, CFDictionaryRef options);

#pragma mark - Drawing / Context

extern CGContextRef SLWindowContextCreate(int cid, uint32_t wid, CFDictionaryRef options);

#pragma mark - Regions

extern CFTypeRef CGRegionCreateEmptyRegion(void);
extern CGError CGSNewRegionWithRect(CGRect *rect, CFTypeRef *region);

#pragma mark - Displays / Spaces

extern CFArrayRef SLSCopyManagedDisplays(int cid);
extern CFStringRef SLSCopyManagedDisplayForWindow(int cid, uint32_t wid);
extern CFStringRef SLSCopyBestManagedDisplayForRect(int cid, CGRect rect);
extern CFStringRef SLSCopyBestManagedDisplayForPoint(int cid, CGPoint point);
extern CFStringRef SLSCopyManagedDisplayForSpace(int cid, uint64_t sid);

extern uint64_t SLSManagedDisplayGetCurrentSpace(int cid, CFStringRef uuid);
extern void SLSManagedDisplaySetCurrentSpace(int cid, CFStringRef display_ref, uint64_t sid);
extern bool SLSManagedDisplayIsAnimating(int cid, CFStringRef uuid);

extern CFArrayRef SLSCopyManagedDisplaySpaces(int cid);
extern CFArrayRef SLSCopySpacesForWindows(int cid, int selector, CFArrayRef window_list);

extern int SLSGetSpaceManagementMode(int cid);
extern int SLSSpaceGetType(int cid, uint64_t sid);
extern CFStringRef SLSSpaceCopyName(int cid, uint64_t sid);

extern void SLSMoveWindowsToManagedSpace(int cid, CFArrayRef window_list, uint64_t sid);
extern CGError SLSProcessAssignToSpace(int cid, pid_t pid, uint64_t sid);
extern CGError SLSProcessAssignToAllSpaces(int cid, pid_t pid);

#pragma mark - Space Visibility

extern void SLSShowSpaces(int cid, CFArrayRef space_list);
extern void SLSHideSpaces(int cid, CFArrayRef space_list);

#pragma mark - Window Lists / Queries

extern CFArrayRef SLSCopyWindowsWithOptionsAndTags(
    int cid, uint32_t owner, CFArrayRef spaces,
    uint32_t options, uint64_t *set_tags, uint64_t *clear_tags
);

extern CFArrayRef SLSCopyAssociatedWindows(int cid, uint32_t wid);

extern CFTypeRef SLSWindowQueryWindows(int cid, CFArrayRef windows, int count);
extern CFTypeRef SLSWindowQueryResultCopyWindows(CFTypeRef window_query);

extern int SLSWindowIteratorGetCount(CFTypeRef iterator);
extern bool SLSWindowIteratorAdvance(CFTypeRef iterator);
extern uint32_t SLSWindowIteratorGetParentID(CFTypeRef iterator);
extern uint32_t SLSWindowIteratorGetWindowID(CFTypeRef iterator);
extern uint64_t SLSWindowIteratorGetTags(CFTypeRef iterator);
extern uint64_t SLSWindowIteratorGetAttributes(CFTypeRef iterator);
extern int SLSWindowIteratorGetLevel(CFTypeRef iterator);

extern CGError SLSRequestNotificationsForWindows(
    int cid,
    uint32_t *window_list,
    int window_count
);

#pragma mark - Process / Focus

extern OSStatus _SLPSGetFrontProcess(ProcessSerialNumber *psn);
extern CGError SLSGetConnectionPSN(int cid, ProcessSerialNumber *psn);
extern CGError SLSConnectionGetPID(int cid, pid_t *pid);
extern CGError SLSGetConnectionIDForPSN(int cid, ProcessSerialNumber *psn, int *psn_cid);
extern CGError _SLPSSetFrontProcessWithOptions(ProcessSerialNumber *psn, uint32_t wid, uint32_t mode);

#pragma mark - Events

extern CGError SLPSPostEventRecordTo(ProcessSerialNumber *psn, uint8_t *bytes);

#pragma mark - Window Detection / Cursor

extern OSStatus SLSFindWindowAndOwner(int cid, int zero, int one, int zero_again, CGPoint *screen_point, CGPoint *window_point, uint32_t *wid, int *wcid);

extern CGError SLSGetCurrentCursorLocation(int cid, CGPoint *point);

#pragma mark - Menu Bar / Dock

extern CFStringRef SLSCopyActiveMenuBarDisplayIdentifier(int cid);
extern CGError SLSSetActiveMenuBarDisplayIdentifier(int cid, CFStringRef uuid, CFStringRef repeat_uuid);

extern CGError SLSSetMenuBarInsetAndAlpha(int cid, double unused1, double unused2, float alpha);
extern CGError SLSGetMenuBarAutohideEnabled(int cid, int *enabled);
extern CGError SLSGetRevealedMenuBarBounds(CGRect *rect, int cid, uint64_t sid);
extern CGError SLSGetDisplayMenubarHeight(uint32_t did, uint32_t *height);

extern CGError SLSGetDockRectWithReason(int cid, CGRect *rect, int *reason);
extern Boolean CoreDockGetAutoHideEnabled(void);
extern void CoreDockGetOrientationAndPinning(int *orientation, int *pinning);

#pragma mark - Transactions

extern CFTypeRef SLSTransactionCreate(int cid);
extern CGError SLSTransactionCommit(CFTypeRef transaction, int synchronous);

extern CGError SLSTransactionSetWindowTransform(CFTypeRef transaction, uint32_t wid, int unknown, int unknown2, CGAffineTransform t);
extern CGError SLSTransactionOrderWindow(CFTypeRef transaction, uint32_t wid, int order, uint32_t rel_wid);
extern CGError SLSTransactionOrderWindowGroup(CFTypeRef transaction, uint32_t wid, int order, uint32_t rel_wid);
extern CGError SLSTransactionSetWindowLevel(CFTypeRef transaction, uint32_t wid, int level);
extern CGError SLSTransactionSetWindowSubLevel(CFTypeRef transaction, uint32_t wid, int sub_level);
extern CGError SLSTransactionSetWindowAlpha(CFTypeRef transaction, uint32_t wid, float alpha);
extern CGError SLSTransactionSetWindowSystemAlpha(CFTypeRef transaction, uint32_t wid, float alpha);

#pragma mark - Misc

extern CGError SLSDisableUpdate(int cid);
extern CGError SLSReenableUpdate(int cid);

extern CFArrayRef SLSHWCaptureWindowList(int cid, uint32_t *window_list, int window_count, uint32_t options);

extern CGError SLSSpaceSetCompatID(int cid, uint64_t sid, int workspace);
extern CGError SLSSetWindowListWorkspace(int cid, uint32_t *window_list, int window_count, int workspace);

extern CGError SLSReassociateWindowsSpacesByGeometry(int cid, CFArrayRef window_list);
extern CGError CoreDockSendNotification(CFStringRef notification, int unknown);
