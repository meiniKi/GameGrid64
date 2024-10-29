
wall = 0.8;
backplate = 0.9;
panel = 192.1;
panel_z = 13.8;
gap = 0.3;
cover_wall = 0.8;
cover_backplate = 0.7;
cover_border_height = 7;
touchin_area_height = 0;
eps=0.02;

arm_len = 40;
arm_snap_r = 1.5;
arm_height = panel_z+backplate;
arm_thick = 1.5;

hole_x = 88;
hole_y = 50;

$fn=30;


    
!union() {
    // backplate    
    translate([0,0,cover_backplate/2])
        cube([panel+2*(wall+gap+cover_wall),panel+2*(wall+gap+cover_wall),cover_backplate], center=true);
    
    // frame
    difference() {
        translate([0,0,(cover_backplate+cover_border_height)/2])
            cube([panel+2*(wall+gap+cover_wall),panel+2*(wall+gap+cover_wall),cover_backplate+cover_border_height], center=true);
        
        translate([0,0,(cover_backplate+cover_border_height+eps)/2])
            cube([panel+2*(wall+gap),panel+2*(wall+gap),cover_backplate+cover_border_height], center=true);
    }
    
    // touching area
    
    difference() {
        translate([0,0,(cover_backplate+touchin_area_height)/2])
            cube([panel+2*(wall+gap+eps),panel+2*(wall+gap+eps),cover_backplate+touchin_area_height], center=true);
        
        translate([0,0,(cover_backplate+touchin_area_height+eps)/2])
            cube([panel,panel,cover_backplate+touchin_area_height], center=true);
    }
    
    
    // arms
    union() {
        translate([0,(panel+arm_thick)/2+wall+gap,arm_height/2])
            cube([arm_len, arm_thick, arm_height], center=true);
    
        translate([0,(panel+2*arm_thick-0.8)/2,-arm_snap_r+arm_height])
            rotate([0,90,0])
                cylinder(arm_len, arm_snap_r, arm_snap_r, center=true);
    }


    union() {
        translate([0,-((panel+arm_thick)/2+wall+gap),arm_height/2])
            cube([arm_len, arm_thick, arm_height], center=true);
    
        translate([0,-(panel+2*arm_thick-0.8)/2,-arm_snap_r+arm_height])
            rotate([0,90,0])
                cylinder(arm_len, arm_snap_r, arm_snap_r, center=true);
    }

}
    

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