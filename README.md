# recode_q

recode_q is a command-line tool converting between the character encodings
using the Qt `QTextStream` and the underlying `QTextCodec` facilities.

It tries to match the UI of [recode_rs](https://github.com/hsivonen/recode_rs/).

This app is less correct and less efficient than recode_rs, so you shouldn't
use this app for any real work. If you need to do encoding conversions, please
use recode_rs instead for correctness.

## Disclaimer

This is a personal project. It has a Mozilla copyright notice, because
I copied and pasted from recode_rs. You should not try to read anything
more into Mozilla's name appearing.
