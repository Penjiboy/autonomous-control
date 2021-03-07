# autonomous-control (Discontinued repo)

This is the repository for UBC Voyage's flagship autonomous control package.
When contributing to this project please follow The Google C++ Style Guide
available at https://google.github.io/styleguide/cppguide.html.

Please do work in a branch titled "lastname_projectName" with one or two word
descriptive project name. Commit early and often, with useful commit messages.
If you feel like you need more than a couple sentences for your commit
message you waited too long to commit.

Make pull requests to dev and close branches once they have been accepted.
Pull requests will not be accepted without complete comments on classes,
methods, and any ambiguous lines of code. Refer to the style guide for comment
guidelines.

Use LogHandle objects in all classes, with any log info that seems useful.
Make use of severity levels, particularly do not spam error unless there is a
critical error.

TODO:
Write copurnicus.cc and copurnicus.h, extend gps.h,
use nmea class (complete) for parsing and fakeserial (complete using file as
source, 1hz refresh rate one line per reading) for data input.
Write mpu9255.h and mpu9255.cc, extend imu.h
Complete servo.h extention for rasb pi library
Clean up i2c.cc and i2c.h, only work on this if you have hardware to test with.

Add any other code that seems like a good idea, don't do any large refactoring
of code, small changes are fine to adapt code to style guidlines.
