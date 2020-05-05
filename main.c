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
    struct gps_data_t   gpsData;
    
    int ret = gps_open( "gpsrv.local", "2947", &gpsData );
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
                    printf( " %f", (float) gpsData.ais.type );
                    printf( " %f", (float) gpsData.ais.mmsi );
                    printf( " %f", (float) gpsData.ais.repeat );
                    
                    printf( " %f", (float) gpsData.attitude.heading );
                    printf( " %f", (float) gpsData.attitude.yaw );
                    printf( " %f", (float) gpsData.attitude.yaw_st );
                    printf( " %f", (float) gpsData.attitude.pitch );
                    printf( " %f", (float) gpsData.attitude.pitch_st );
                    printf( " %f", (float) gpsData.attitude.roll );
                    printf( " %f", (float) gpsData.attitude.roll_st );
                    printf( " %f", (float) gpsData.attitude.acc_x );
                    printf( " %f", (float) gpsData.attitude.gyro_x );
                    printf( " %f", (float) gpsData.attitude.mag_st );
                    
                    printf( " %f", (float) gpsData.fix.epx );
                    printf( " %f", (float) gpsData.fix.epy );
                    
                    printf( " %f", (float) gpsData.navdata.compass_deviation );
                    printf( " %f", (float) gpsData.navdata.compass_heading );
                    printf( " %f", (float) gpsData.navdata.compass_status );
                    printf( " %f", (float) gpsData.navdata.crosstrack_error );
                    
                    printf( " %f", (float) gpsData.osc.delta );
                    
                    printf( " %f", (float) gpsData.satellites_used );
                    printf( " %f", (float) gpsData.satellites_visible );
                    printf( " %f", (float) gpsData.skyview[0].PRN );
                    printf( " %f", (float) gpsData.skyview[0].azimuth );
                    printf( " %f", (float) gpsData.skyview[0].elevation );
                    
                }
            }
        }
    }
}

