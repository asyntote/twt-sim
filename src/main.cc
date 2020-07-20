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
#include <twt_gkmake.h>
#include <twt_define.h>

gim_obj 		* gim = NULL;
_gim_list		* people = NULL;
_twt_st			* twt = NULL;
_twt_man		* Tman = NULL;
_gim_checksum	* cs = NULL;
_gim_rand		* mt = NULL;

int main( int argc , char **argv ) {

    if ( gim_check_version(2,8) != __GIM_OK ) {
        printf( "%s\n\n" , gim_version() );
        printf( "Gim is not updated at the required version.\n" );
        printf( "For %s is necessary Gim >= 2.8\n" , argv[0] );
        exit( __GIM_ERROR );
    }
    
    gim_set_application_name( "TWT-Sim" );
    gim = new gim_obj;
    
    printf( "TWT-Sim : Tag Walking Technology Simulator\n" );
    printf( "Test suite for checking the TWT consistency algorithm\n" );
    printf( "Powered by: %s\n" , gim_version() );
    printf( "Ran by: %s@%s\n\n" , gim->identity->login() , gim->identity->node() );
	puts( "TWT initializing...\n" );	

	printf( "  TWT status: creating...");
	twt_sleep( 1.0 );
	twt = (_twt_st *)gim->memory->Alloc( sizeof( _twt_st ) ); 
	twt->status = __INIT_ST;
	twt->ar = __UNKN;									//	andata o ritorno
	twt->perc_evasione = __PERC_EVASIONE;				//	% evasione
	twt->capienza = __CAPIENZA_MEZZO;					//	# passeggeri max
	twt->intensita = __CURRENT_CROWD * __CROWD_CONST;	//	flusso persone
	twt->num_passeggeri = 0;
	twt->fermata_corrente = __UP_CAPO;					//	Tempi di percorrenza
	twt->arrivo_capolinea_sec = __CAPA_TM;				//	 .
	twt->capolinea_sec = __CAPF_TM;						//	 .
	twt->partenza_capolinea_sec = __CAPP_TM;			//	 .
	twt->viaggio_sec = __VIAG_TM;						//	 .
	twt->approccio_sec = __APPR_TM;						//	 .
	twt->fermata_sec = __FERM_TM;						//	 .
	twt->chporte_sec = __CHIU_TM;						//	-
	twt->errore = __GIM_OK;								//	Errore da iniettare
	printf( "done!\n");

	twt_sleep( 0.2 );
	printf( "  Current status: %s\n" , get_state_name( twt->status ) );
	
	printf( "  Passengers: creating...");
	people = new _gim_list;
	Tman = NULL;
	cs = new _gim_checksum;
	mt = new _gim_rand;
	
	twt_sleep( 1.0 );
	printf( "done!\n");
	twt_sleep( 1.0 );
	twt->status = __STAR_ST;
	float vgf = 0.0;
	
	
	__MAIN_LOOP( 10 ) {
		
		twt->ar = __ANDATA;
		vgf = (float)vg + 0.1;
		viaggio( vgf );
		twt->ar = __RITORNO;
		vgf += 0.1;
		viaggio( vgf );
		
	}
	
	puts("");
	gim->memory->Free( (void *)twt );
	delete cs;
	delete people;   
    delete gim;
}


