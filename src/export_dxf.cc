/*
 *  OpenSCAD (www.openscad.org)
 *  Copyright (C) 2009-2011 Clifford Wolf <clifford@clifford.at> and
 *                          Marius Kintel <marius@kintel.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, you have permission to link this program
 *  with the CGAL library and distribute executables, as long as you
 *  follow the requirements of the GNU GPL in regard to all of the
 *  software in the executable aside from CGAL.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "export.h"
#include "polyset.h"
#include "polyset-utils.h"
#include "dxfdata.h"

/*!
	Saves the current Polygon2d as DXF to the given absolute filename.
 */

void export_dxf_header(std::ostream &output,double xMin,double yMin,double xMax,double yMax) {
	
	// based on: https://github.com/mozman/ezdxf/tree/master/examples_dxf
	// note: Minimal_DXF_AC1009.dxf - does not work in Adobe Illustrator
	// Minimal_DXF_AC1006.dxf

	output
		<< "999\n" << "DXF from OpenSCAD\n";

	//
	// SECTION 1
	//

	/* --- START ---
	0
	SECTION
	2
	HEADER
	9
	$ACADVER
	1
	AC1006
	9
	$INSBASE
	10
	0.0
	20
	0.0
	30
	0.0
	*/

	output
		<< "  0\n" << "SECTION\n"
		<< "  2\n" << "HEADER\n"
		<< "  9\n" << "$ACADVER\n"
		<< "  1\n" << "AC1006\n"
		<< "  9\n" << "$INSBASE\n"
		<< " 10\n" << "0.0\n"
		<< " 20\n" << "0.0\n"
		<< " 30\n" << "0.0\n";

	/* --- LIMITS ---
	9
	$EXTMIN
	10
	0.0
	20
	0.0
	9
	$EXTMAX
	10
	1000.0
	20
	1000.0
	9
	$LINMIN
	10
	0.0
	20
	0.0
	9
	$LINMAX
	10
	1000.0
	20
	1000.0
	0
	ENDSEC
	*/

	// might not be necessary to set the actual limits
	// but some apps might rely on it
	output
		<< "  9\n" << "$EXTMIN\n"
		<< " 10\n" << xMin << "\n"
		<< " 20\n" << yMin << "\n"
		<< "  9\n" << "$EXTMAX\n"
		<< " 10\n" << xMax << "\n"
		<< " 20\n" << yMax << "\n";

	output
		<< "  9\n" << "$LINMIN\n"
		<< " 10\n" << xMin << "\n"
		<< " 20\n" << yMin << "\n"
		<< "  9\n" << "$LINMAX\n"
		<< " 10\n" << xMax << "\n"
		<< " 20\n" << yMax << "\n";

	output 
		<< "  0\n" << "ENDSEC\n";

	//
	// SECTION 2
	//

	output
		<< "  0\n" << "SECTION\n";

	output
		<< "  2\n" << "TABLES\n";

	/* --- LINETYPE ---
	0
	SECTION
	2
	TABLES
	0
	TABLE
	2
	LTYPE
	70
	1
	0
	LTYPE
	2
	CONTINUOUS
	70
	64
	3
	Solid line
	72
	65
	73
	0
	40
	0.000000
	0
	ENDTAB
	*/

	output
		<< "  0\n" << "TABLE\n"
		<< "  2\n" << "LTYPE\n"
		<< " 70\n" << "1\n"

		<< "  0\n" << "LTYPE\n"
		<< "  2\n" << "CONTINUOUS\n"
		<< " 70\n" << "64\n"
		<< "  3\n" << "Solid line\n"
		<< " 72\n" << "65\n"
		<< " 73\n" << "0\n"
		<< " 40\n" << "0.000000\n"

		<< "  0\n" << "ENDTAB\n";

	/* --- LAYERS ---
	0
	TABLE
	2
	LAYER
	70
	6
	0
	LAYER
	2
	1
	70
	64
	62
	7
	6
	CONTINUOUS
	0
	LAYER
	2
	2
	70
	64
	62
	7
	6
	CONTINUOUS
	0
	ENDTAB
	*/

	output
		<< "  0\n" << "TABLE\n"
		<< "  2\n" << "LAYER\n"
		<< " 70\n" << "6\n"

		<< "  0\n" << "LAYER\n"
		<< "  2\n" << "1\n"
		<< " 70\n" << "64\n"
		<< " 62\n" << "7\n"
		<< "  6\n" << "CONTINUOUS\n"

		<< "  0\n" << "LAYER\n"
		<< "  2\n" << "2\n"
		<< " 70\n" << "64\n"
		<< " 62\n" << "7\n"
		<< "  6\n" << "CONTINUOUS\n"

		<< "  0\n" << "ENDTAB\n";

	/* --- STYLE ---
	0
	TABLE
	2
	STYLE
	70
	0
	0
	ENDTAB
	0
	ENDSEC
	*/

	output
		<< "  0\n" << "TABLE\n"
		<< "  2\n" << "STYLE\n"
		<< " 70\n" << "0\n"
		<< "  0\n" << "ENDTAB\n";

	output
		<< "  0\n" << "ENDSEC\n";

	//
	// SECTION 3
	//

	/* --- BLOCKS ---
	0
	SECTION
	2
	BLOCKS
	0
	ENDSEC
	*/

	output
		<< "  0\n" << "SECTION\n"
		<< "  2\n" << "BLOCKS\n"
		<< "  0\n" << "ENDSEC\n";

}

void export_dxf(const Polygon2d &poly, std::ostream &output)
{
	setlocale(LC_NUMERIC, "C"); // Ensure radix is . (not ,) in output

	// find limits
	double xMin, yMin, xMax, yMax;
	xMin = yMin = std::numeric_limits<double>::max(),
	xMax = yMax = std::numeric_limits<double>::min();
	for(const auto &o : poly.outlines()) {
		for (unsigned int i=0; i<o.vertices.size(); ++i) {
			const Vector2d &p = o.vertices[i];
			if ( xMin > p[0] ) xMin = p[0];
			if ( xMax < p[0] ) xMax = p[0];
			if ( yMin > p[1] ) yMin = p[1];
			if ( yMax < p[1] ) yMax = p[1];
		}
	}

	export_dxf_header(output,xMin,yMin,xMax,yMax);

	// --- TO BE DELETED ---
	// // Some importers needs a BLOCKS section to be present
	// // e.g. Inkscape 1.1 still needs it 
	// // output  << "  0\n" << "SECTIONxxx\n"
	// // 		<< "  2\n" << "BLOCKS\n"
	// // 		<< "  0\n" << "ENDSEC\n";
	// output  << "  0\n" << "SECTION\n"
	// 		<< "  2\n" << "ENTITIES\n";

	// ENTITIES:
    // https://help.autodesk.com/view/ACD/2017/ENU/?guid=GUID-3610039E-27D1-4E23-B6D3-7E60B22BB5BD
	// https://documentation.help/AutoCAD-DXF/WS1a9193826455f5ff18cb41610ec0a2e719-795d.htm
    // https://documentation.help/AutoCAD-DXF/WS1a9193826455f5ff18cb41610ec0a2e719-7a3d.htm
    
	for(const auto &o : poly.outlines()) {
		switch( o.vertices.size() ) {
		case 1: {
			// POINT: just in case it's supported in the future
			// https://help.autodesk.com/view/ACD/2017/ENU/?guid=GUID-9C6AD32D-769D-4213-85A4-CA9CCB5C5317
            // https://documentation.help/AutoCAD-DXF/WS1a9193826455f5ff18cb41610ec0a2e719-79f2.htm
			const Vector2d &p = o.vertices[0];
			output  << "  0\n" << "POINT\n"
					<< "100\n" << "AcDbEntity\n"
					<< "  8\n" << "1\n" 		// layer 1
					<< "100\n" << "AcDbPoint\n"
					<< " 10\n" << p[0] << "\n"  // x
					<< " 20\n" << p[1] << "\n"; // y
			} break;
		case 2: {
			// LINE: just in case it's supported in the future
            // https://help.autodesk.com/view/ACD/2017/ENU/?guid=GUID-FCEF5726-53AE-4C43-B4EA-C84EB8686A66
            // https://documentation.help/AutoCAD-DXF/WS1a9193826455f5ff18cb41610ec0a2e719-79fe.htm
			// The [X1 Y1 X2 Y2] order is the most common and can be parsed linearly.
			// Some libraries, like the python libraries dxfgrabber and ezdxf, cannot open [X1 X2 Y1 Y2] order.
			const Vector2d &p1 = o.vertices[0];
			const Vector2d &p2 = o.vertices[1];
			output  << "  0\n" << "LINE\n"
					<< "100\n" << "AcDbEntity\n"
					<< "  8\n" << "1\n" 		 // layer 1
					<< "100\n" << "AcDbLine\n"
					<< " 10\n" << p1[0] << "\n"  // x1
					<< " 20\n" << p1[1] << "\n"  // y1
					<< " 11\n" << p2[0] << "\n"  // x2
					<< " 21\n" << p2[1] << "\n"; // y2
			} break;
		default:
			// LWPOLYLINE
            // https://help.autodesk.com/view/ACD/2017/ENU/?guid=GUID-748FC305-F3F2-4F74-825A-61F04D757A50
            // https://documentation.help/AutoCAD-DXF/WS1a9193826455f5ff18cb41610ec0a2e719-79fc.htm
			output  << "  0\n" << "LWPOLYLINE\n"
					<< "100\n" << "AcDbEntity\n"
					<< "  8\n" << "1\n" 		            // layer 1
					<< "100\n" << "AcDbPolyline\n"
					<< " 90\n" << o.vertices.size() << "\n" // number of vertices
					<< " 70\n" << "1\n";                    // closed = 1
			for (unsigned int i=0; i<o.vertices.size(); ++i) {
				const Vector2d &p = o.vertices[i];
				output  << " 10\n" << p[0] << "\n"
						<< " 20\n" << p[1] << "\n";
			}
			break;
		}

		// --- TO BE DELETED ---
		// each segment as separate line
		// for (unsigned int i=0; i<o.vertices.size(); ++i) {
		// 	const Vector2d &p1 = o.vertices[i];
		// 	const Vector2d &p2 = o.vertices[(i+1)%o.vertices.size()];
		// 	output  << "  0\n" << "LINE\n"
		//			<< "100\n" << "AcDbEntity\n"
		//			<< "  8\n" << "0\n" 		 // layer 0
		//			<< "100\n" << "AcDbLine\n"
		// 			<< " 10\n" << p1[0] << "\n"  // x1
		// 			<< " 20\n" << p1[1] << "\n"  // y1
		// 			<< " 11\n" << p2[0] << "\n"  // x2
		// 			<< " 21\n" << p2[1] << "\n"; // y2
		// }
	}

	output << "  0\n" << "ENDSEC\n";

	// --- TO BE DELETED ---
	// Some importers (e.g. Inkscape) needs an OBJECTS section with a DICTIONARY entry.
	// as of Inkscape 1.0, not needed anymore
	// output
	// 	<< "  0\n" << "SECTION\n"
	// 	<< "  2\n" << "OBJECTS\n"
	// 	<< "  0\n" << "DICTIONARY\n"
	// 	<< "  0\n" << "ENDSEC\n";

	output << "  0\n" << "EOF\n";

	setlocale(LC_NUMERIC, ""); // set default locale
}

void export_dxf(const shared_ptr<const Geometry> &geom, std::ostream &output)
{
	if (const auto geomlist = dynamic_pointer_cast<const GeometryList>(geom)) {
		for(const auto &item : geomlist->getChildren()) {
			export_dxf(item.second, output);
		}
	} else if (dynamic_pointer_cast<const PolySet>(geom)) {
		assert(false && "Unsupported file format");
	} else if (const auto poly = dynamic_pointer_cast<const Polygon2d>(geom)) {
		export_dxf(*poly, output);
	} else {
		assert(false && "Export as DXF for this geometry type is not supported");
	}
}
