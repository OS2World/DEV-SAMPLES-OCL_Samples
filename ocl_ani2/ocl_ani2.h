/* St‚phane Charette, stephane@venus.ubishops.ca
 * IBM Open Class Library Animation Sample #2
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997July06
 */

#ifndef OCL_ANI2_H
#define OCL_ANI2_H

#define DLG_RCID           0x1000
#define CANVAS_RCID        0x1001
#define BMP_PERSON1_RCID   0x1002   // orange
#define BMP_PERSON2_RCID   0x1003   // blue
#define BMP_PERSON3_RCID   0x1004   // green
#define BMP_PERSON4_RCID   0x1005   // red
#define BMP_PERSON5_RCID   0x1006   // gray
#define PTR_MOVE_RCID      0x1007

#define MNU_RCID           0x2000
#define MNU_DELETE_PERSON  0x2001
#define MNU_CREATE_PERSON  0x2002
#define MNU_CLONE_PERSON   0x2003

#define MNU_MOVE_PERSON    0x2004
#define MNU_MOVE_SET       0x2005
#define MNU_MOVE_STOP      0x2006

// create menus have the same ID as the bitmaps
#define MNU_CREATE_ORANGE  BMP_PERSON1_RCID
#define MNU_CREATE_BLUE    BMP_PERSON2_RCID
#define MNU_CREATE_GREEN   BMP_PERSON3_RCID
#define MNU_CREATE_RED     BMP_PERSON4_RCID
#define MNU_CREATE_GRAY    BMP_PERSON5_RCID

#endif
