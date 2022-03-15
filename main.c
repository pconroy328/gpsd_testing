/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: pconroy
 *
 * Created on May 5, 2020, 3:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gps.h>
#include <errno.h>

/*
 * 
 */
int main(int argc, char** argv) 
{
    puts( "Pass in Host string!" );
    
    struct gps_data_t   gpsData;
    
    int ret = gps_open( argv[1], "2947", &gpsData );
    if (ret >= 0) {
        (void) gps_stream( &gpsData, (WATCH_ENABLE | WATCH_JSON), NULL );

        while (1) {
            errno = 0;
                
            if (gps_waiting( &gpsData, 5000000L )) {            // wait five seconds
#ifdef STRETCH                    
                ret = gps_read( &gpsData, NULL, 0 );
#else                    
                ret = gps_read( &gpsData );
#endif                    
                if (ret < 0) 
                    fprintf( stderr, "GPS Device is unavailable!  errno = %d\n", errno );

                else if (ret == 0)
                    fprintf( stderr, "GPS Device is there but there's no data to be read!  errno = %d\n", errno );

                else {
                    puts( "gps data - ais structure" );
                    printf( "type     %u\n", gpsData.ais.type );
                    printf( "mmsi     %u\n", gpsData.ais.mmsi );
                    printf( "repeat   %u\n", gpsData.ais.repeat );
                    
                    puts( "gps data - attitude structure" );
                    printf( "heading   %f\n", (float) gpsData.attitude.heading );
                    printf( "yaw       %f\n", (float) gpsData.attitude.yaw );
                    printf( "yaw_str   %c\n", gpsData.attitude.yaw_st );
                    printf( "pitch     %f\n", (float) gpsData.attitude.pitch );
                    printf( "pitch str %c\n", gpsData.attitude.pitch_st );
                    printf( "roll      %f\n", (float) gpsData.attitude.roll );
                    printf( "roll str  %c\n", gpsData.attitude.roll_st );
                    printf( "acc_x     %f\n", (float) gpsData.attitude.acc_x );
                    printf( "gyro_x    %f\n", (float) gpsData.attitude.gyro_x );
                    printf( "mag str   %c\n", gpsData.attitude.mag_st );
                    
                    puts( "gps data - fix structure" );
                    printf( "latitude           %f\n", (float) gpsData.fix.latitude );
                    printf( "lat uncertainty    %f\n", (float) gpsData.fix.epy );
                    printf( "longtitude         %f\n", (float) gpsData.fix.longitude );
                    printf( "long uncertainty   %f\n", (float) gpsData.fix.epx );
                    printf( "mode               %f\n", (float) gpsData.fix.mode );
                    printf( "speed              %f\n", (float) gpsData.fix.speed );
                    printf( "speed uncertainty  %f\n", (float) gpsData.fix.eps );
                    printf( "track              %f\n", (float) gpsData.fix.track );
                    printf( "track uncertainty  %f\n", (float) gpsData.fix.epd );
                    printf( "climb              %f\n", (float) gpsData.fix.climb );
                    printf( "climb uncertainty  %f\n", (float) gpsData.fix.epc );
                    printf( "altitude           %f\n", (float) gpsData.fix.altitude );
                    printf( "alt uncertainty    %f\n", (float) gpsData.fix.epv );
              
#ifndef STRETCH                    
                    puts( "gps data - navdata structure" );
                    printf( "compass deviation %f\n", (float) gpsData.navdata.compass_deviation );
                    printf( "compass heading   %f\n", (float) gpsData.navdata.compass_heading );
                    printf( "compass status    %f\n", (float) gpsData.navdata.compass_status );
                    printf( "crosstrack_error  %f\n", (float) gpsData.navdata.crosstrack_error );
#endif                    
#ifdef STRETCH                    
                    puts( "gps data - osc structure" );
                    printf( "delta    %f\n", (float) gpsData.osc.delta );
#endif
                    
                    puts( "gps data - satellites and skyview structure" );
                    printf( "satellites used      %d\n", gpsData.satellites_used );
                    printf( "satellites visible   %d\n", gpsData.satellites_visible );
                    printf( "sat[0] PRN           %d\n", gpsData.skyview[0].PRN );
                    printf( "sat[0] azimuth       %d\n", gpsData.skyview[0].azimuth );
                    printf( "sat[0] elevation     %d\n", gpsData.skyview[0].elevation );
                }
                
                sleep( 5 );
            }
        }
    }
}

