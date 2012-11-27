/*
 * Copyright (C) 2012 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Voss <thomas.voss@canonical.com>
 */

#include <ubuntu/application/sensors/ubuntu_application_sensors.h>
#include <ubuntu/application/ui/ubuntu_application_ui.h>
#include <ubuntu/ui/ubuntu_ui_session_service.h>

#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *android_dlopen(const char *filename, int flag);
extern void *android_dlsym(void *handle, const char *symbol);

#ifdef __cplusplus
}
#endif

namespace
{

struct Bridge
{
    static const char* path_to_library()
    {
        return "/system/lib/libubuntu_application_api.so";
    }
    
    Bridge() : lib_handle(android_dlopen(path_to_library(), RTLD_LAZY))
    {
        assert(lib_handle && "Error loading ubuntu_application_api");
    }

    ~Bridge()
    {
        // TODO android_dlclose(libcamera_handle);
    }

    void* resolve_symbol(const char* symbol) const
    {
        return android_dlsym(lib_handle, symbol);
    }
    
    void* lib_handle;
};

static Bridge bridge;

}

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/*********** Implementation starts here *******************/
/**********************************************************/

#define DLSYM(fptr, sym) if (*(fptr) == NULL) { *(fptr) = (void *) bridge.resolve_symbol(sym); }
    
#define IMPLEMENT_FUNCTION0(return_type, symbol)  \
    return_type symbol()                          \
    {                                             \
        static return_type (*f)() = NULL;         \
        DLSYM(&f, #symbol);                \
        return f();}
    
#define IMPLEMENT_FUNCTION1(return_type, symbol, arg1) \
    return_type symbol(arg1 _1)                        \
    {                                                  \
        static return_type (*f)(arg1) = NULL;          \
        DLSYM(&f, #symbol);                     \
        return f(_1); }

#define IMPLEMENT_VOID_FUNCTION1(symbol, arg1)               \
    void symbol(arg1 _1)                                     \
    {                                                        \
        static void (*f)(arg1) = NULL;                       \
        DLSYM(&f, #symbol);                           \
        f(_1); }

#define IMPLEMENT_FUNCTION2(return_type, symbol, arg1, arg2)    \
    return_type symbol(arg1 _1, arg2 _2)                        \
    {                                                           \
        static return_type (*f)(arg1, arg2) = NULL;             \
        DLSYM(&f, #symbol);                              \
        return f(_1, _2); }

#define IMPLEMENT_VOID_FUNCTION2(symbol, arg1, arg2)            \
    void symbol(arg1 _1, arg2 _2)                               \
    {                                                           \
        static void (*f)(arg1, arg2) = NULL;                    \
        DLSYM(&f, #symbol);                              \
        f(_1, _2); }

#define IMPLEMENT_VOID_FUNCTION3(symbol, arg1, arg2, arg3)      \
    void symbol(arg1 _1, arg2 _2, arg3 _3)                      \
    {                                                           \
        static void (*f)(arg1, arg2, arg3) = NULL;              \
        DLSYM(&f, #symbol);                                     \
        f(_1, _2, _3); }

#define IMPLEMENT_VOID_FUNCTION7(symbol, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
    void symbol(arg1 _1, arg2 _2, arg3 _3, arg4 _4, arg5 _5, arg6 _6, arg7 _7) \
    {                                                                   \
        static void (*f)(arg1, arg2, arg3, arg4, arg5, arg6, arg7) = NULL; \
        DLSYM(&f, #symbol);                                             \
        f(_1, _2, _3, _4, _5, _6, _7); }


    IMPLEMENT_VOID_FUNCTION2(ubuntu_application_ui_init, int, char**);
    IMPLEMENT_FUNCTION0(StageHint, ubuntu_application_ui_setup_get_stage_hint);
    IMPLEMENT_FUNCTION0(FormFactorHint, ubuntu_application_ui_setup_get_form_factor_hint);
    IMPLEMENT_VOID_FUNCTION1(ubuntu_application_ui_start_a_new_session, SessionCredentials*);
    IMPLEMENT_VOID_FUNCTION2(ubuntu_application_ui_create_display_info, ubuntu_application_ui_physical_display_info*, size_t);
    IMPLEMENT_VOID_FUNCTION1(ubuntu_application_ui_destroy_display_info, ubuntu_application_ui_physical_display_info);
    IMPLEMENT_FUNCTION1(int32_t, ubuntu_application_ui_query_horizontal_resolution, ubuntu_application_ui_physical_display_info);
    IMPLEMENT_FUNCTION1(int32_t, ubuntu_application_ui_query_vertical_resolution, ubuntu_application_ui_physical_display_info);    
    IMPLEMENT_VOID_FUNCTION7(ubuntu_application_ui_create_surface, ubuntu_application_ui_surface*, const char*, int, int, SurfaceRole, input_event_cb, void*);
    IMPLEMENT_VOID_FUNCTION1(ubuntu_application_ui_destroy_surface, ubuntu_application_ui_surface);
    IMPLEMENT_FUNCTION1(EGLNativeWindowType, ubuntu_application_ui_surface_to_native_window_type, ubuntu_application_ui_surface);
    IMPLEMENT_VOID_FUNCTION3(ubuntu_application_ui_move_surface_to, ubuntu_application_ui_surface, int, int);
    IMPLEMENT_VOID_FUNCTION3(ubuntu_application_ui_resize_surface_to, ubuntu_application_ui_surface, int, int);

// Session service
IMPLEMENT_FUNCTION1(int, ubuntu_ui_session_properties_get_application_instance_id, ubuntu_ui_session_properties);
IMPLEMENT_FUNCTION1(const char*, ubuntu_ui_session_properties_get_desktop_file_hint, ubuntu_ui_session_properties);
IMPLEMENT_VOID_FUNCTION1(ubuntu_ui_session_install_session_lifecycle_observer, ubuntu_ui_session_lifecycle_observer*);
IMPLEMENT_VOID_FUNCTION1(ubuntu_ui_session_focus_running_session_with_id, int);
IMPLEMENT_VOID_FUNCTION3(ubuntu_ui_session_snapshot_running_session_with_id, int, ubuntu_ui_session_service_snapshot_cb, void*); 
IMPLEMENT_VOID_FUNCTION1(ubuntu_ui_session_trigger_switch_to_well_known_application, ubuntu_ui_well_known_application);
// Accelerometer service
IMPLEMENT_VOID_FUNCTION1(ubuntu_sensor_install_accelerometer_observer, ubuntu_accelerometer_observer*);



#ifdef __cplusplus
}
#endif
