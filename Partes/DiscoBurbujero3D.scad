use <engranajes.scad>

origen = [0,0,0];
espesor = 1.5;
diametro_rueda = 220;
orificio = 7.5;


module Rueda()
{
    translate(origen)
    cylinder(h = espesor, r1 = diametro_rueda / 2, r2 = diametro_rueda / 2, center = false, $fn = 100);

}

module OrificiosGr()
{
    translate(origen + [(diametro_rueda/2)-20,0,0])
        gear (number_of_teeth=80,
            circular_pitch=1*80, diametral_pitch=false,
            pressure_angle=20,
            clearance = 0.2,
            gear_thickness=10,
            rim_thickness=10,
            rim_width=10,
            hub_thickness=10,
            hub_diameter=113,
            bore_diameter=0,
            circles=0,
            backlash=0,
            twist=0,
            involute_facets=5,
            flat=false);

}

module OrificiosCh()
{
    translate(origen + [(diametro_rueda/2)-9,0,0])
        gear (number_of_teeth=50,
            circular_pitch=1*50, diametral_pitch=false,
            pressure_angle=20,
            clearance = 0.2,
            gear_thickness=10,
            rim_thickness=10,
            rim_width=10,
            hub_thickness=10,
            hub_diameter=113,
            bore_diameter=0,
            circles=0,
            backlash=0,
            twist=0,
            involute_facets=5,
            flat=false);

}

// Main -->
difference()
{
    Rueda();

    translate(origen) cylinder(h = espesor, r1 = orificio/2, r2 = orificio/2, center = false, $fn = 10);

    OrificiosGr();
    rotate([0,0,30])  OrificiosGr();
    rotate([0,0,60])  OrificiosGr();
    rotate([0,0,90])  OrificiosGr();
    rotate([0,0,120]) OrificiosGr();
    rotate([0,0,150]) OrificiosGr();
    rotate([0,0,180]) OrificiosGr();
    rotate([0,0,210]) OrificiosGr();
    rotate([0,0,240]) OrificiosGr();
    rotate([0,0,270]) OrificiosGr();
    rotate([0,0,300]) OrificiosGr();
    rotate([0,0,330]) OrificiosGr();

    rotate([0,0,15])  OrificiosCh();
    rotate([0,0,45])  OrificiosCh();
    rotate([0,0,75])  OrificiosCh();
    rotate([0,0,105]) OrificiosCh();
    rotate([0,0,135]) OrificiosCh();
    rotate([0,0,165]) OrificiosCh();
    rotate([0,0,195]) OrificiosCh();
    rotate([0,0,225]) OrificiosCh();
    rotate([0,0,255]) OrificiosCh();
    rotate([0,0,285]) OrificiosCh();
    rotate([0,0,315]) OrificiosCh();
    rotate([0,0,345]) OrificiosCh();

}
