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
#include <twt_define.h>

int main( int argc , char **argv ) {

    if ( gim_check_version(2,8) != __GIM_OK ) {
        printf( "%s\n\n" , gim_version() );
        printf( "Gim is not updated at the required version.\n" );
        printf( "For %s is necessary Gim >= 2.8\n" , argv[0] );
        exit( __GIM_ERROR );
    }
    
    gim_set_application_name( "TWT-Sim" );
    gim_obj * gim = new gim_obj;
    
    printf( "TWT-Sim : Tag Walking Technology Simulator\n" );
    printf( "Test suite for checking the TWT consistency algorithm\n" );
    printf( "Powered by: %s\n" , gim_version() );
    printf( "Ran by: %s@%s\n\n" , gim->identity->login() , gim->identity->node() );
	puts( "TWT initializing...\n" );	
	
	printf( "  TWT status: creating...");
	usleep( 50 );
	_twt_st	* twt = (_twt_st *)gim->memory->Alloc( sizeof( _twt_st ) ); 
	twt->status = __INIT_ST;
	twt->perc_non_paganti = 15;				//	%
	twt->capienza = 120;					//	persone max
	twt->intensita = 0;						//	flusso persone
	twt->fermata_corrente = __UP_CAPO;		//	Capolinea 
	twt->capolinea_sec = 30;
	twt->chporte_sec = 2;
	twt->viaggio_sec = 15;
	twt->approccio_sec = 5;	
	twt->errore = __GIM_NO;					//	Errore da iniettare
	
	printf( "done!\n");
	
	printf( "  Passengers: creating...");
	_gim_list	* people = new _gim_list;
	_twt_man	* Tman = NULL;
	
	for( int c = 0 ; c < PEOPLE_NUMBER ; c++ ) {
		Tman = new_twt_man( gim );
		people->add_item( (void *)Tman );
		usleep( 50 );
	}
	printf( "done!\n");
	puts( "\n-------------------------------------------------" );
	


	
	puts("");
	gim->memory->Free( (void *)twt );
	delete people;   
    delete gim;
}



_twt_man *	new_twt_man( gim_obj * gim ) {
	_twt_man	* Tman = NULL;
	Tman = (_twt_man *)gim->memory->Alloc( sizeof( _twt_man ) );
	Tman->type = __UNKN;
	Tman->linea = 1;
	Tman->active = __NOT_ACTIVE;
	Tman->id_salita = __GIM_NO;
	Tman->on_board = __GIM_NO;
	Tman->id_discesa = __GIM_NO;
	Tman->status = __UNDIFINED;
	__GIM_CLEAR( Tman->code_id , GIM_MD5_SIZE , char );
	Tman->twt_str_code = _UN;
	Tman->twt_mid_code = _UN;
	Tman->twt_end_code = _UN;
	return Tman;
} 

