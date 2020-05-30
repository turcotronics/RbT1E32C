#
# Main Makefile. This is basically the same as a component makefile.
#
# This Makefile should, at the very least, just include $(SDK_PATH)/make/component.mk. By default, 
# this will take the sources in the src/ directory, compile them and link them into 
# lib(subdirectory_name).a in the build directory. This behaviour is entirely configurable,
# please read the SDK documents if you need to do this.
#
COMPONENT_EMBED_FILES := www/index.html.gz
COMPONENT_EMBED_FILES += www/style.css.gz
COMPONENT_EMBED_FILES += www/script.js.gz
COMPONENT_EMBED_FILES += www/favicon.ico.gz
