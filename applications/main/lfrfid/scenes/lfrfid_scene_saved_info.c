#include "../lfrfid_i.h"

void lfrfid_scene_saved_info_on_enter(void* context) {
    LfRfid* app = context;
    Widget* widget = app->widget;

    FuriString* tmp_string = furi_string_alloc();
    furi_string_printf(tmp_string, "Name: %s\n", furi_string_get_cstr(app->file_name));

    const char* protocol = protocol_dict_get_name(app->dict, app->protocol_id);
    const char* manufacturer = protocol_dict_get_manufacturer(app->dict, app->protocol_id);

    if(strcmp(protocol, manufacturer) != 0) {
        furi_string_cat_printf(tmp_string, "\e#%s %s\n", manufacturer, protocol);
    } else {
        furi_string_cat_printf(tmp_string, "\e#%s\n", protocol);
    }

    FuriString* render_data = furi_string_alloc();
    protocol_dict_render_data(app->dict, render_data, app->protocol_id);
    furi_string_cat(tmp_string, render_data);
    furi_string_free(render_data);

    widget_add_text_scroll_element(widget, 0, 0, 128, 64, furi_string_get_cstr(tmp_string));

    view_dispatcher_switch_to_view(app->view_dispatcher, LfRfidViewWidget);
    furi_string_free(tmp_string);
}

bool lfrfid_scene_saved_info_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    bool consumed = false;
    return consumed;
}

void lfrfid_scene_saved_info_on_exit(void* context) {
    LfRfid* app = context;
    widget_reset(app->widget);
}
