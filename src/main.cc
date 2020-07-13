/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2020 asyntote <asyntote@gmail.com>
 * 
 * TWT-Sim is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TWT-Sim is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <unistd.h>             
#include <gim/gim.h>

#include <twt_gkmake.h>

int main( int argc , char **argv ) {

    if ( gim_check_version(2,8) != __GIM_OK ) {
        printf( "%s\n\n" , gim_version() );
        printf( "Gim is not updated at the required version.\n" );
        printf( "For %s is necessary Gim >= 2.8\n" , argv[0] );
        exit( -1 );
    }
    
    gim_set_application_name( "test" );
    gim_obj * gim = new gim_obj;
    
    printf( "TWT-Sim : Tag Walking Technology Simulator\n" );
    printf( "Test suite for checking the TWT consistency algorithm\n" );
    printf( "Powered by: %s\n" , gim_version() );
    printf( "Ran by: %s@%s\n\n" , gim->identity->login() , gim->identity->node() );
    
	_gim_string passw;
	if ( argc > 1 ) {	
		puts( argv[1] );
	    passw.set( argv[1] );
	    passw.cat( " - " );
    }
    passw.cat( gim->identity->login() );
    passw.cat( "@" );
    passw.cat( gim->identity->node() );
	printf( "%x - %s: %s\n" , gim->checksum->chsum( gim->checksum->sha512( passw.c_str() , passw.length() ) ) , passw.c_str() , gim->checksum->sha512( passw.c_str() , passw.length() ) );

	_gim_ascii_buffer * a = new _gim_ascii_buffer;
	a->set_dimension( 100000 );

    MTRand	* r = new MTRand;
    r->seed( gim->checksum->chsum( gim->checksum->sha512( passw.c_str() , passw.length() ) ) );
    for( _gim_Uint32 c = 0 ; c < a->get_dimension()  ; c++ ) {
//    	printf( "%d scrivo" , c );
    	a->append( "%c" , r->randUInt8() ); 
    }

    _gim_file   f( "./buffer_mt_to_test" , __GIM_FILE_POINTER , __GIM_WRITE );
    f.flush( a->get_buffer() , a->get_dimension() );
    f.close();
        
	delete a;	    
    delete r;
    delete gim;
}

