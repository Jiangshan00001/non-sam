# non-sam
this is a totally reimplemention of sam voice synthesis. inspired by sam.

ref：https://github.com/s-macke/SAM


the difference with SAM:
1. the code is totally reimplemention
2. the voice data is from espeak-ng, so could support more language
3. the code size is limited to <64k in bin executable, so that it could port to other chip easily.

/// this is a totally reimplemention of formant voice synthesis software.
/// it is highly inspaired by sam & espeak.
/// it's phoneme data is from espeak-ng.
/// it support chinese and english by default.
/// the code size is limited to <64kbytes.
/// the programming language is limited to c.
///
///

/// translation steps:

/// 1. text-to-text: 100$ -> hundred dollars, June 1->first of June

/// 2. text-to-phoneme:

/// 3. tone settings.

/// 4. phonme-to-wave.

///
/// implemention:

/// 1. phoneme->code  TODO

/// 2. phoneme->wave  TODO

/// 3. pinyin->phoneme->wave  TODO

/// 4. english->phoneme->wave  TODO




