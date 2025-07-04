## Summary

* To be able to use the latest/adequate version of sass, install sassc
* meson will regenerate the CSS every time you modify the SCSS files.
* Note that meson always builds out-of-tree, so the modified css files will
  appear in your builddir.

## Theme Variants

The Adwaita theme comes in 4 variants: light, dark, hc (highcontrast) and
hc-dark (highcontrast inverse). The generated CSS files for the variants
are called `Adwaita-$variant.css`. For technical reasons, GTK adds one level
of include wrappers around these, which are called `gtk-$variant.css`.

## How to Tweak the Theme

Adwaita is a complex theme, so to keep it maintainable it's written and
processed in SASS. The generated CSS is then transformed into a gresource file
during gtk build and used at runtime in a non-legible or editable form.

It is very likely your change will happen in the _common.scss file. That's where
all the widget selectors are defined. Here's a rundown of the "supporting"
stylesheets, that are unlikely to be the right place for a drive by stylesheet
fix:

_colors.scss        - global color definitions. We keep the number of defined
                      colors to a necessary minimum, most colors are derived
                      from a handful of basics. It covers both the light variant
                      and the dark variant.

_colors-public.scss - SCSS colors exported through gtk to allow for 3rd party
                      apps color mixing.

_drawing.scss       - drawing helper mixings/functions to allow easier
                      definition of widget drawing under specific context. This
                      is why Adwaita isn't 15000 LOC.

_common.scss        - actual definitions of style for each widget. This is
                      where you are likely to add/remove your changes.

You can read about SASS at http://sass-lang.com/documentation/. Once you make
your changes to the _common.scss file, libadwaita will rebuild the CSS files.
