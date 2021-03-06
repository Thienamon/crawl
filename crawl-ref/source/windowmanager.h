#pragma once

#ifdef USE_TILE_LOCAL

#include "tiletex.h"

enum wm_event_type
{
    WME_NOEVENT = 0,
    WME_ACTIVEEVENT,
    WME_KEYDOWN,
    WME_KEYUP,
    WME_KEYPRESS,
    WME_MOUSEMOTION,
    WME_MOUSEBUTTONUP,
    WME_MOUSEBUTTONDOWN,
    WME_QUIT,
    WME_CUSTOMEVENT,
    WME_RESIZE,
    WME_EXPOSE,
    WME_NUMEVENTS = 15
};

struct wm_keysym
{
    unsigned char scancode;
    int sym;
    unsigned char key_mod;
    unsigned int unicode;
};

struct wm_active_event
{
    unsigned char type;
    unsigned char gain;
    unsigned char state;
};

struct wm_keyboard_event
{
    unsigned char type;
    unsigned char state;
    wm_keysym keysym;
};

struct wm_resize_event
{
    unsigned char type;
    int w, h;
};

struct wm_expose_event
{
    unsigned char type;
};

struct wm_quit_event
{
    unsigned char type;
};

struct wm_custom_event
{
    unsigned char type;
    int code;
    void *data1;
    void *data2;
};

// Basically a generic SDL_Event
struct wm_event
{
    unsigned char type;
    wm_active_event active;
    wm_keyboard_event key;
    MouseEvent mouse_event;
    wm_resize_event resize;
    wm_expose_event expose;
    wm_quit_event quit;
    wm_custom_event custom;
};

// custom timer callback function
typedef unsigned int (*wm_timer_callback)(unsigned int interval, void* param);

class WindowManager
{
public:
    // To silence pre 4.3 g++ compiler warnings
    virtual ~WindowManager() {};

    // Static Alloc/deallocators
    // Note: Write this function in each implementation-specific file,
    // e.g. windowmanager-sdl.cc has its own WindowManager::create().
    static void create();
    static void shutdown();

    // Class functions
    virtual int init(coord_def *m_windowsz, int *densityNum,
                     int *densityDen) = 0;

    // Environment state functions
    virtual void set_window_title(const char *title) = 0;
    virtual bool set_window_icon(const char* icon_name) = 0;
    virtual key_mod get_mod_state() const = 0;
    virtual void set_mod_state(key_mod mod) = 0;

    // System time functions
    virtual unsigned int set_timer(unsigned int interval,
                                   wm_timer_callback callback) = 0;
    virtual void remove_timer(unsigned int timer_id) = 0;
    virtual unsigned int get_ticks() const = 0;
    virtual void delay(unsigned int ms) = 0;

    // Event functions
    virtual int raise_custom_event() = 0;
    virtual int wait_event(wm_event *event) = 0;
    virtual unsigned int get_event_count(wm_event_type type) = 0;
    virtual void show_keyboard() = 0;

    // Display functions
    virtual void resize(coord_def &m_windowsz) = 0;
    virtual void swap_buffers() = 0;
    virtual int screen_width() const = 0;
    virtual int screen_height() const = 0;
    virtual int desktop_width() const = 0;
    virtual int desktop_height() const = 0;

    // Texture loading
    virtual bool load_texture(GenericTexture *tex, const char *filename,
                              MipMapOptions mip_opt, unsigned int &orig_width,
                              unsigned int &orig_height,
                              tex_proc_func proc = nullptr,
                              bool force_power_of_two = true) = 0;
};

// Main interface for UI functions
extern WindowManager *wm;

#endif //USE_TILE_LOCAL
