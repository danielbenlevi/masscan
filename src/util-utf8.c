#include "util-utf8.h"

/*****************************************************************************
 *****************************************************************************/
unsigned
utf8_seqlen(unsigned char lead)
{
    if ((lead & 0x80) == 0x00)
        return 1;            
    if ((lead & 0xC0) == 0x80)
        return 1;             
    if ((lead & 0xE0) == 0xC0)
        return 2;             
    if ((lead & 0xF0) == 0xE0)
        return 3;           
    if ((lead & 0xF8) == 0xF0)
        return 4;           
    if ((lead & 0xFC) == 0xF8)
        return 5;            
    if ((lead & 0xFE) == 0xFC)
        return 6;
    return 1;
}

/*****************************************************************************
 *****************************************************************************/
unsigned
utf8_encode_len(unsigned codepoint)
{
    if (codepoint < 0x80)
        return 1;
    else if (codepoint < 0x800)
        return 2;
    else if (codepoint < 0x10000)
        return 3;
    else if (codepoint < 0x200000)
        return 4;
    else if (codepoint < 0x4000000)
        return 5;
    else
        return 6;
}

/*****************************************************************************
 *****************************************************************************/
size_t
utf8_encode(unsigned codepoint, unsigned char *out)
{
    unsigned len = utf8_encode_len(codepoint);

    switch (len) {
    case 1:
        out[0] = (unsigned char)codepoint;
        break;
    case 2:
        out[0] = (unsigned char)(0xC0 | ((codepoint >>  6) & 0x1F));
        out[1] = (unsigned char)(0x80 | ((codepoint >>  0) & 0x3F));
        break;
    case 3:
        out[0] = (unsigned char)(0xE0 | ((codepoint >> 12) & 0x0F));
        out[1] = (unsigned char)(0x80 | ((codepoint >>  6) & 0x3F));
        out[2] = (unsigned char)(0x80 | ((codepoint >>  0) & 0x3F));
        break;
    case 4:
        out[0] = (unsigned char)(0xF0 | ((codepoint >> 18) & 0x07));
        out[1] = (unsigned char)(0x80 | ((codepoint >> 12) & 0x3F));
        out[2] = (unsigned char)(0x80 | ((codepoint >>  6) & 0x3F));
        out[3] = (unsigned char)(0x80 | ((codepoint >>  0) & 0x3F));
        break;
    case 5:
        out[0] = (unsigned char)(0xF8 | ((codepoint >> 24) & 0x03));
        out[1] = (unsigned char)(0x80 | ((codepoint >> 18) & 0x3F));
        out[2] = (unsigned char)(0x80 | ((codepoint >> 12) & 0x3F));
        out[3] = (unsigned char)(0x80 | ((codepoint >>  6) & 0x3F));
        out[4] = (unsigned char)(0x80 | ((codepoint >>  0) & 0x3F));
        break;
    case 6:
    default:
        out[0] = (unsigned char)(0xFC | ((codepoint >> 30) & 0x01));
        out[1] = (unsigned char)(0x80 | ((codepoint >> 24) & 0x3F));
        out[2] = (unsigned char)(0x80 | ((codepoint >> 18) & 0x3F));
        out[3] = (unsigned char)(0x80 | ((codepoint >> 12) & 0x3F));
        out[4] = (unsigned char)(0x80 | ((codepoint >>  6) & 0x3F));
        out[5] = (unsigned char)(0x80 | ((codepoint >>  0) & 0x3F));
        break;
    }

    return len;
}
