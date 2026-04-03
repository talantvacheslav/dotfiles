typedef struct ExternalBarStrut ExternalBarStrut;
struct ExternalBarStrut {
    Window win;
    int left, right, top, bottom;
    int left_start_y,   left_end_y;
    int right_start_y,  right_end_y;
    int top_start_x,    top_end_x;
    int bottom_start_x, bottom_end_x;
    ExternalBarStrut *next;
};

static int externalbars_hasstrut(Window w);
static void externalbars_register(Window w);
static void externalbars_unregister(Window w);
static void externalbars_apply(Monitor *m);
static void externalbars_reapply_all(void);
