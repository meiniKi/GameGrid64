
wall = 0.8;
backplate = 1.8;
panel = 192.1;
panel_z = 13.8;

eps=0.02;

hole_x = 88;
hole_y = 50;

$fn=30;

difference() {
    translate([0,0,(panel_z+backplate)/2])
        cube([panel+2*wall, panel+2*wall, panel_z+backplate], center=true);
    
   translate([0,0,panel_z/2+backplate+eps])
        cube([panel,panel, panel_z], center=true);
    
    hole(hole_x,hole_y,2);
    hole(-hole_x,hole_y,2);
    hole(hole_x,-hole_y,2);
    hole(-hole_x,-hole_y,2);
    
    hole(hole_y,hole_x,2);
    hole(-hole_y,hole_x,2);
    hole(hole_y,-hole_x,2);
    hole(-hole_y,-hole_x,2);
    
    // USB C
    translate([-(panel/2-5-4),panel/2,20/2+backplate-0.8])
        cube([12, 30, 20], center=true);
    
    // micro USB
    translate([0,panel/2,20/2+backplate-0.8])
        cube([8, 20, 20], center=true);
        
    // Bootsel
    hole(4,panel/2-14.5-3,3);

    // Button
    hole(panel/2-59,panel/2-8,7);
    hole(-(panel/2-59),panel/2-8,7);
    
    // air
    for ( x = [-60:20:60]) {
        for ( y = [-60:20:60]) {
            hole(x,y,7);
        }
    }
    
    // hang
    hole(0,-panel/2+15,2);
}


module hole(x,y,r) {
    translate([x,y,0])
        cylinder(10, r, r, center=true);
    
}