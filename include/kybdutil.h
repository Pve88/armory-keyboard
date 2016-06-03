#ifndef KYBDUTIL_H
#define KYBDUTIL_H

#include "layouts.h"

/**
 * Set the layout to use. Must be called before any other function in this
 * unit is called.
 *
 * @param[in] lo pointer to layout to use
 */
void set_layout(struct layout *lo);

/**
 * Generates and returns an 8-byte USB HID keyboard report.
 *
 * This function accepts a char * to an 8-byte block that should be filled
 * with the generated report. The report is generated by passing the Unicode
 * codepoints of the characters that should be generated if the report is sent
 * to an HID host.
 *
 * Example call to send GUI + r, which has 1 escape code and 1 ASCII character:
 * make_hid_report(report, 1, 2, GUI, 'r');
 *
 * The 8-byte char array pointed to by report will then contain an HID report
 * specifying the GUI + r key combo (1 special key, 2 keys total).
 *
 * This function assumes the short report format, so at most 6 keys may be
 * be passed. If more than 6 are passed, the first 6 will be used.
 *
 * Report format:
 * Byte    0: Bit field for modifier keys (shift, alt, win, etc)
 * Byte    1: Reserved (0x00)
 * Bytes 2-7: usage id's of character data (see spec)
 *
 * Uppercase alpha character are handled by converting them to lowercase,
 * coding for the lowercase key, and indicating l+r shift in the modifier byte.
 * See HID Usage Tables, Page 0x07 for this conversion.
 *
 * For a detailed explanation of the report format, see:
 * USB Device Class Definition for Human Interface Devices (HID) Appendix B.1
 * USB HID Usage Tables, Section 10 (Keyboards)
 *
 * numescape and argc parameters must satisfy the following conditions:
 *  1 <= argc <= 6
 *  0 <= numescape <= argc
 *
 * If they do not, behavior is undefined. If argc does not match the number of
 * arguments passed, behavior is undefined. If the layout has not been set
 * with set_layout
 *
 * @param[out] report pointer to 8 byte array of char to store the result in
 * @param[in] the number of escape characters passed
 * @param[in] argc the total number of characters passed
 * @param[in] ... the UTF-8 codepoints to encode into the report, escapes first
 * @return 0 on success, -1 if a character with no known mapping is encountered
 */
int make_hid_report(char *report, int numescape, int argc, ...);

/**
 * Generates and returns an 8-byte USB HID keyboard report.
 *
 * This function accepts a char * to an 8-byte block that should be filled
 * with the generated report. The report is generated by passing the Unicode
 * codepoints of the characters that should be generated if the report is sent
 * to an HID host.
 *
 * Example call to send GUI + r, which has 1 escape code and 1 ASCII character:
 * char chars[2] = { GUI, 'r' };
 * make_hid_report(report, 1, 2, &chars);
 *
 * The 8-byte char array pointed to by report will then contain an HID report
 * specifying the GUI + r key combo (1 special key, 2 keys total).
 *
 * This function assumes the short report format, so at most 6 keys may be
 * be passed. If more than 6 are passed, the first 6 will be used.
 *
 * Report format:
 * Byte    0: Bit field for modifier keys (shift, alt, win, etc)
 * Byte    1: Reserved (0x00)
 * Bytes 2-7: usage id's of character data (see spec)
 *
 * Uppercase alpha character are handled by converting them to lowercase,
 * coding for the lowercase key, and indicating l+r shift in the modifier byte.
 * See HID Usage Tables, Page 0x07 for this conversion.
 *
 * For a detailed explanation of the report format, see:
 * USB Device Class Definition for Human Interface Devices (HID) Appendix B.1
 * USB HID Usage Tables, Section 10 (Keyboards)
 *
 * numescape and argc parameters must satisfy the following conditions:
 *  1 <= argc <= 6
 *  0 <= numescape <= argc
 *
 * If they do not, behavior is undefined. If argc does not match the number of
 * arguments passed, behavior is undefined.
 *
 * @param[out] report pointer to 8 byte array of char to store the result in
 * @param[in] the number of escape characters passed
 * @param[in] argc the total number of characters passed
 * @param[in] chars pointer to array of chars to encode into the array, escapes first
 * @return 0 on success, -1 if a character with no known mapping is encountered, or if
 * NULL is passed as the last parameter
 */
int make_hid_report_arr(char *report, int numescape, int argc, uint32_t *codepoints);

#endif
