// twt_functions.cc
//
// Copyright (C) 2020 - asyntote
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include <stdio.h>
#include <unistd.h>             
#include <gim/gim.h>

#include <twt_gkmake.h>
#include <twt_define.h>


	char	Linea1[][64] = {	
		"CARICAMENTO/ACQUARIO",				//	 0
		"GRAMSCI 1/METRO' DARSENA",			// 	 1
		"GRAMSCI 2/STATUTO",				//	 2
		"GRAMSCI 3/COMMENDA",				//	 3
		"MARITTIMA/PRINCIPE FS",			//	 4
		"BUOZZI 1/PIAZZA SAN TEODORO",		//	 5
		"BUOZZI 2/METRO' DINEGRO",			//	 6
		"FRANCIA 2/MATITONE",				//	 7
		"FRANCIA 3/STAZIONE FS",			//	 8
		"BURANELLO 1/BARABINO",				//	 9
		"BURANELLO 2/GIOVANETTI",			//	10
		"AVIO 1/MOLTENI",					//	11
		"PACINOTTI/FIUMARA",				//	12
		"PIERAGOSTINI/FIUMARA",				//	13
		"ANSALDO/MASSENA",					//	14
		"CORNIGLIANO 1/GIARDINI MELIS",		//	15
		"CORNIGLIANO 2/RIZZOLIO",			//	16
		"CORNIGLIANO 3/PIAZZA CONTI",		//	17
		"CORNIGLIANO 4/STAZIONE FS",		//	18
		"SIFFREDI 1/TONALE",				//	19
		"SIFFREDI 2/ACCIAIO",				//	20
		"SIFFREDI 3/CALCINARA",				//	21
		"HERMADA/MENOTTI",					//	22
		"PUCCINI 1/TRAVI",					//	23
		"PUCCINI 2/SESTRI FS AEROPORTO",	//	24
		"SOLIMAN/CERRUTI",					//	25
		"MERANO 1/VILLA ROSSI",				//	26
		"MERANO 2/MONFALCONE",				//	27
		"MERANO 3/AMIU",					//	28
		"MULTEDO/VILLA CHIESA",				//	29
		"RONCHI/VIGILI DEL FUOCO",			//	30
		"LUNGOMARE DI PEGLI 1/VARENNA",		//	31
		"LUNGOMARE DI PEGLI 2/PEGLI FS",	//	32
		"PEGLI 5/CASTELLUCCIO",				//	33
		"PRA' 1/BIOMEDICAL",				//	34
		"PEGLI 3/ASL",						//	35
		"PEGLI 4/LIDO",						//	36
		"PEGLI 5/CASTELLUCCIO",				//	37
		"PRA' 1/BIOMEDICAL",				//	38
		"PRA' 2/FERRIERE",					//	39
		"PRA' 3/PRA' FS",					//	40
		"PRA' 5/CORDANIERI",				//	41
		"PRA' 6/LAURA",						//	42							
		"PRA' 7/PALMARO CENTRO",			//	43
		"PRA' 8/DE MARI",					//	44
		"PRA' 9/VILLA PODESTA'",			//	45
		"PRA' 10/VERRINA",					//	46
		"VOLTRI/VOLTRI FS",					//	47
		"VERITA'/VOLTRI FS",				//	48
		"CAMOZZINI 1/GAGGERO",				//	49
		"CAMOZZINI 2/PRATI",				//	50
		"CAMOZZINI 3/CADUTI",				//	51
		"CAMOZZINI/CAPOLINEA",				//	52
	};



_twt_man *	new_twt_man( void ) {
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


const char *		get_state_name( _gim_flag st ) {
	switch ( st ) {
		case __INIT_ST : {
			return __INIT;
		}
		case __STAR_ST : {
			return __STAR;
		}
		case __CAPA_ST : {
			return __CAPA;
		}
		case __CAPO_ST : {
			return __CAPO;
		}
		case __CAPP_ST : {
			return __CAPP;
		}
		case __VIAG_ST : {
			return __VIAG;
		}
		case __APPR_ST : {
			return __APPR;
		}
		case __FERM_ST : {
			return __FERM;
		}
		case __CHIU_ST : {
			return __CHIU;
		}
		default: {
			return "Unknown";
		}
	}
}


void	twt_sleep( float sec ) {
	usleep( (_gim_Uint32)( sec * 1000000.0 ) );
}


void 	viaggio( _gim_Uint8 vg ) {
	_gim_Uint8 from = 0 , to = 0;
	if ( twt->ar == __ANDATA ) {
		from = __UP_CAPO;
		to = __DW_CAPO;  
	}
	else if ( twt->ar == __RITORNO ) {
		from = __DW_CAPO-1;
		to = __UP_CAPO;  
	}

	for( _gim_int8 f = from ; twt->ar==__ANDATA?f<=to:f>=to ; ) {
		switch ( twt->status ) {
			case __STAR_ST : {
				puts(   "\n\e[1;33m-------------------------------------------------\e[0m" );
				twt_sleep( 0.5 );
				printf( "  Travel \e[1;33m#%d\e[0m\n" , vg );
				printf( "  Current status: \e[1;33m%s\e[0m\n" , get_state_name( twt->status ) );
				puts(   "\e[1;33m-------------------------------------------------\e[0m\n" );
				twt_sleep( __STAR_TM );
				twt->status = __CAPA_ST;
				break;
			}
			case __CAPA_ST : {								//	CAPOLINEA ----------------------------------------------------------------------------
				puts( "\n\e[1;31m-------------------------------------------------" );
				puts( "-------------------------------------------------" );
				puts( "-------------------------------------------------\e[0m" );
				printf( "  Travel \e[1;33m#%d\e[0m - Bus terminus: \e[1;31m%s\e[0m\n" , vg , Linea1[ f ] );
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->arrivo_capolinea_sec );
				twt->status = __CAPO_ST;
				break;
			}
			case __CAPO_ST : {
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->capolinea_sec );
				twt->status = __CAPP_ST;
				break;
			}
			case __CAPP_ST : {
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->partenza_capolinea_sec );
				twt->status = __VIAG_ST;
				twt->ar==__ANDATA?f++:f--;
				puts( "\e[1;31m-------------------------------------------------" );
				puts( "-------------------------------------------------" );
				puts( "-------------------------------------------------\e[0m\n" );
				break;
			}
			case __VIAG_ST : {								//	VIAGGIO  ----------------------------------------------------------------------------
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->viaggio_sec );
				twt->status = __APPR_ST;
				puts( "-------------------------------------------------\n" );
				break;
			}
			case __APPR_ST : {								//	FERMATA ----------------------------------------------------------------------------
				printf( "  Bus stop \e[0;32m#%d\e[0m - Bust stop: \e[0;32m%s\e[0m\n" , f , Linea1[ f ] );
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->approccio_sec );
				twt->status = __FERM_ST;
				break;
			}
			case __FERM_ST : {
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				
				
				
				
				
				twt_sleep( twt->fermata_sec );
				twt->status = __CHIU_ST;
				twt->ar==__ANDATA?f++:f--;
				break;
			}
			case __CHIU_ST : {
				printf( "  Current status: " );
				printf( "%s\n" , get_state_name( twt->status ) );
				twt_sleep( twt->chporte_sec );
				if ( ( f == __DW_CAPO ) || ( f == __UP_CAPO ) )
					twt->status = __CAPA_ST;
				else
					twt->status = __VIAG_ST;
				break;
			}
		}
	}
}



void	ps_salita( _gim_int8 fermata ) {
	_gim_Uint8	cr = twt->intensita;
	_gim_Uint8	salite = 0;
	_twt_man	* man = NULL;	
	 
	if ( ( fermata == __DW_CAPO ) || ( fermata == __UP_CAPO ) ) {
		cr = __CROWD_LO;
	}
	salite = mt->randInt( cr );
	for( _gim_Uint32 cnt = 0 ; cnt < salite ; cnt++ ) {
		man = (_twt_man *)gim->memory->Alloc( sizeof( _twt_man ) );
//		strcpy( man->code_id , 	
	
	}

}



void	ps_discesa( _gim_int8 fermata , gim_obj * gim , _gim_list * ps , _twt_st * twt ) {



}
