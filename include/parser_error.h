#ifndef PARSER_ERROR_H
# define PARSER_ERROR_H

#define	ERR_MAT "Expected format: material <name> [c <R,G,B>] [a <R,G,B>] [d <value>] [s <value>] [sh <value>] [p <pattern>] [refl <value>] [trans <value>] [ri <value>]"
#define ERR_INC_AMB "Expected format: A <ambient_ratio> <R,G,B>"
#define ERR_INC_CAM "Expected format: C <x,y,z> <orientation x,y,z> <FOV>"
#define ERR_SPHERE "Expected format: sp <x,y,z> <diameter> <R,G,B> [material]"
#define ERR_LIGHT "Expected format: L <x,y,z> <brightness_ratio> <R,G,B>"
#define ERR_PLANE "Expected format: pl <x,y,z> <normal vector> <R,G,B> [material]"
#define ERR_CYLINDER "Expected format: cy <x,y,z> <axis vector> <diameter> <height> <R,G,B> [material]"
#define ERR_CONE "Expected format: cone <base x,y,z> <axis x,y,z> <radius> <height> <is open> <R,G,B> [material]"
#define ERR_CUBE "Expected format: cube <center x,y,z> <axis vector> <width> <height> <depth> <R,G,B> [material]"
#define	RATIO_INVALID "Invalid ambient lighting ratio"
#define RATIO_RANGE "Ambient lighting ratio out of range"
#define RGB_LEN "RGB elements count incorrect."
#define RGB_INVALID "Invalid RGB numbers."
#define RGB_RANGE "RGB values out of range"
#define MALLOC_FAIL "Error\nMemory allocation failed"
#define	ARG_MANY "Error\nToo many arguments"
#define ARG_FEW "Error\nMissing .rt file argument"
#define FILE_FORMAT "Error\nInvalid file extension"
#define FOV_M "Invalid FOV"
#define FOV_RANGE_M "FOV out of range"
#define POV_M "POV elements count incorrect."
#define POV_INVALID_M "Invalid POV numbers."
#define POV_RANGE_M "POV values out of range"
#define OR_M "Orientation Vector elements count incorrect."
#define OR_INVALID_M "Invalid Orientation Vector numbers."
#define OR_RANGE_M "Orientation Vector values out of range"
#define L_RATIO_M "Invalid light brightness ratio"
#define L_RATIO_RANGE_M "Light brightness ratio out of range"
#define POS_M "Light point coordinates count incorrect"
#define POS_INVALID_M "Invalid light point coordinates"
#define POS_RANGE_M "Light point coordinate values out of range"
#define	D_INVALID "Invalid diameter"
#define D_RANGE_M "Diameter out of range"
#define	H_INVALID "Invalid Height"
#define H_RANGE_M "Height out of range"
#define	DEPTH_INVALID "Invalid Depth"
#define DEPTH_RANGE_M "Depth out of range"
#define	W_INVALID "Invalid Width"
#define W_RANGE_M "Width out of range"
#define CENT_M "Center coordinates count incorrect"
#define CENT_INVALID_M "Invalid center coordinates"
#define CENT_RANGE_M "Center coordinate values out of range"
#define NORMAL_M "Normal vector count incorrect"
#define NORMAL_INVALID_M "Invalid Normal vector"
#define NORMAL_RANGE_M "Normal vector values out of range"
#define POINT_COUNT_M "Point coordinates count incorrect."
#define POINT_INVALID_M "Invalid point coordinates."
#define POINT_RANGE_M "Point coordinates values out of range."
#define	R_INVALID "Invalid Radius"
#define R_RANGE_M "Radius out of range"
#define	DIF_INVALID_M "Invalid Diffuse"
#define DIF_RANGE_M "Diffuse out of range"
#define ERR_BOOL "Boolean for 'is open' must be 0 (closed) or 1 (open)"
#define MATERIAL_N "Material not found"
#define	SPEC_INVALID_M "Invalid Specular"
#define SPEC_RANGE_M "Specular out of range"
#define	SHINE_INVALID_M "Invalid Shininess"
#define SHINE_RANGE_M "Shininess out of range"
#define	REF_INVALID_M "Invalid Reflectivity"
#define REF_RANGE_M "Reflectivity out of range"
#define	TRANS_INVALID_M "Invalid Transparency"
#define TRANS_RANGE_M "Transparency out of range"
#define	RIF_INVALID_M "Invalid Refractive Index"
#define RIF_RANGE_M "Refractive Index out of range"
#define UNKNOWN_ELEMENT "Error\nUnknown element found."
#define MULTI_AMBIENT "Error\nMultiple instances of Ambient Lighting found."
#define AMBIEN_FOUND "Error\nNo Ambient Lighting found."
#define MULTI_CAMERA "Error\nMultiple instances of Camera found."
#define NO_CAMERA "Error\nNo Camera found."
#define MULTI_LIGHT "Error\nMultiple instances of Light found."
#define NO_LIGHT "Error\nNo Light found."

typedef enum e_error_type
{
	RATIO,
	RATIO_OUT_RANGE,
	RGB,
	RGB_VALID,
	RGB_OUT_RANGE,
	FOV,
	FOV_RANGE,
	POV,
	POV_INVALID,
	POV_RANGE,
	OR,
	OR_INVALID,
	OR_RANGE,
	L_RATIO,
	L_RATIO_RANGE,
	POS,
	POS_INVALID,
	POS_RANGE,
	DIAM,
	DIAM_RANGE,
	CENT,
	CENT_INVALID,
	CENT_RANGE,
	NORMAL,
	NORMAL_INVALID,
	NORMAL_RANGE,
	POINT,
	POINT_INVALID,
	POINT_RANGE,
	HEIGHT_VALID,
	HEIGHT_RANGE,
	RADIUS,
	RADIUS_RANGE,
	OPEN,
	OPEN_RANGE,
	WIDTH_VALID,
	WIDTH_RANGE,
	DEPTH_VALID,
	DEPTH_RANGE,
	DIF_VALID,
	DIF_RANGE,
	SPEC_VALID,
	SPEC_RANGE,
	SHINE_VALID,
	SHINE_RANGE,
	REF_VALID,
	REF_RANGE,
	TRANS_VALID,
	TRANS_RANGE,
	RIF_VALID,
	RIF_RANGE,
}	t_error_type;

#endif