# recode_q

recode_q is a command-line tool converting between the character encodings
using the Qt `QTextStream` and the underlying `QTextCodec` facilities.

It tries to match the UI of [recode_rs](https://github.com/hsivonen/recode_rs/).
Most UI strings are copied from there, hence the license files come from there.
(I wrote recode_q on my own time as a way to experiment with Qt out of curiosity
about Qt, but I have no interest in imposing licensing notices or requirements
beyond those inherited from recode_rs.)

This app is less correct and less efficient than recode_rs, so you shouldn't
use this app for any real work. If you need to do encoding conversions, please
use recode_rs instead for correctness.
