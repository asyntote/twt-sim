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
		case __CAPF_ST : {
			return __CAPF;
		}
		case __CAPI_ST : {
			return __CAPI;
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


void 	viaggio( float vg ) {
	_gim_Uint8 from = 0 , to = 0;
	if ( twt->ar == __ANDATA ) {
		from = __UP_CAPO;
		to = __DW_CAPO;
	}
	else if ( twt->ar == __RITORNO ) {
		from = __DW_CAPO-1;
		to = __UP_CAPO;  
	}

	for( _gim_int8 f = from ; ( ( twt->ar==__ANDATA?f<=to:f>=to ) && ( twt->errore == __GIM_OK ) ) ; ) {
		switch ( twt->status ) {
			case __STAR_ST : {
				puts(   "\n\e[1;33m-------------------------------------------------\e[0m" );
				twt_sleep( 0.5 );
				printf( "  Travel \e[1;33m#%1.1f\e[0m\n" , vg );
				printf( "  Current status: \e[1;33m%s\e[0m\n" , get_state_name( twt->status ) );
				puts(   "\e[1;33m-------------------------------------------------\e[0m\n" );
				twt_sleep( __STAR_TM );
				twt->status = __CAPA_ST;
				break;
			}
			case __CAPA_ST : {								//	CAPOLINEA ----------------------------------------------------------------------------
				puts( "\n\e[1;31m-------------------------------------------------" );
				TWT_DEBUG puts( "-------------------------------------------------" );
				puts( "-------------------------------------------------\e[0m" );
				printf( "  Travel \e[1;33m#%1.1f\e[0m\n" , vg );
				printf( "  Bus stop \e[0;32m#%d\e[0m - Bus terminus: \e[1;31m%s\e[0m\n" , f , Linea1[ f ] );

				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->arrivo_capolinea_sec );
				twt->status = __CAPF_ST;
				break;
			}
			case __CAPF_ST : {
				TWT_DEBUG printf( "  Current status: " );
				TWT_DEBUG printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				
				ps_discesa( f , vg );			

				twt_sleep( twt->capolinea_sec );
				twt->status = __CAPI_ST;
				twt->ar==__ANDATA?f++:f--;
				break;
			}
			case __CAPI_ST : {
				printf( "  New travel starting: \e[0;1m%1.1f\e[0m\n" , vg );

				ps_salita( twt->ar==__ANDATA?f-1:f+1 , vg );
				
				twt_sleep( twt->capolinea_sec );
				twt->status = __CAPP_ST;
				break;
			}
			case __CAPP_ST : {
				printf( "  Passengers on board: \e[0;1m%d\e[0m\n" , twt->num_passeggeri );
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->partenza_capolinea_sec );
				twt->status = __VIAG_ST;
				printf( "  Travel \e[1;33m#%1.1f\e[0m starting\n" , vg );
				puts( "\e[1;31m-------------------------------------------------" );
				TWT_DEBUG puts( "-------------------------------------------------" );
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
				printf( "  Bus stop \e[0;32m#%d\e[0m - Bus stop: \e[0;32m%s\e[0m\n" , f , Linea1[ f ] );
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
				twt_sleep( twt->approccio_sec );
				twt->status = __FERM_ST;
				break;
			}
			case __FERM_ST : {
				printf( "  Current status: " );
				printf( "\e[0;1m%s\e[0m\n" , get_state_name( twt->status ) );
							
				ps_discesa( f , vg );
				ps_salita( f , vg );
				
				twt_sleep( twt->fermata_sec );
				twt->status = __CHIU_ST;
				twt->ar==__ANDATA?f++:f--;
				break;
			}
			case __CHIU_ST : {
				printf( "  Passengers on board: \e[0;1m%d\e[0m\n" , twt->num_passeggeri );
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



void	ps_salita( _gim_int8 fermata , float vg ) {
	_gim_Uint8	cr = twt->intensita;
	_gim_Uint8	salite = 0;
	_twt_man	* man = NULL;	
	 
	
	if ( twt->num_passeggeri < twt->capienza ) {   	
		if ( ( fermata == __DW_CAPO ) || ( fermata == __UP_CAPO ) ) {
			cr = __CROWD_LO * __CROWD_CONST;
		}
		salite = mt->randInt( cr );
		if ( ( salite + twt->num_passeggeri ) > twt->capienza )
			salite = twt->capienza - twt->num_passeggeri;
		printf( "    Num salite: %d\n" , salite ); 
		for( _gim_Uint32 cnt = 0 ; cnt < salite ; cnt++ ) {
			man = (_twt_man *)gim->memory->Alloc( sizeof( _twt_man ) );
			
			man->type = __UNKN;
			man->linea = __LINEA;
			man->active = __ACTIVE;
			man->id_viaggio = vg;
			man->id_salita = fermata;
			man->on_board = __GIM_YES;
			man->id_discesa = __UNKN;
			man->perc_decisione = 10;
			man->status = __UNKN;
			man->optic_count = __GIM_YES;
			strcpy( man->code_id , rf_id_passeggero() ); 	
			
			man->twt_str_code = __UNKN;
			man->twt_mid_code = __UNKN;
			man->twt_end_code = __UNKN;
			
			people->add_item( (void *)man );
			
			twt->num_passeggeri++;
			
			printf("        Salito passeggero: %s\n" , man->code_id );
			
		}
	}
}


_gim_flag	man_decisione( _gim_int32 id ) {
	_twt_man	* man = NULL;
	_gim_flag 	res = __UNKN;

	TWT_DEBUG printf( "  -- ricevuto id (%d)\n" , id );
	man = (_twt_man *)people->get_item( id );
	res = mt->stat_distr_over_100_percentage( man->perc_decisione );
	if ( res == __GIM_NO ) { 
		man->perc_decisione += 2;
		return 0;
	}
	return id;
}


void	ps_discesa( _gim_int8 fermata , float vg ) {
	_gim_Uint8	cr = twt->intensita;
	_gim_Uint8	discese = 0;
	_twt_man	* man = NULL;
	_gim_Uint32 last_ps = people->items();
	_gim_int32	old    = __UNKN;
	_gim_int32	oldest = 0;
	_gim_int32	oldest_id = 0;
	_gim_int32	dec_id = __UNKN;
	 
	discese = mt->randInt( cr );
	if ( discese > twt->num_passeggeri )
		discese = twt->num_passeggeri;
	if ( ( fermata == __DW_CAPO ) || ( fermata == __UP_CAPO ) ) {
		for( _gim_int32 cnt = 1 ; cnt <= last_ps ; cnt++ ) {
			man = (_twt_man *)people->get_item( cnt );
			if ( man->active == __ACTIVE ) {			
				TWT_DEBUG printf( "Cur viaggio: %1.1f - Viaggio effettuato: %1.1f - ciclo %d - %s - %s\n" , vg , man->id_viaggio , cnt , man->code_id , man->on_board==__GIM_YES?"ON BOARD":"NOT ON BOARD" );
				if ( ( man->id_viaggio == vg ) && ( man->on_board == __GIM_YES ) ) {
					man->id_discesa = fermata;
					man->active = __NOT_ACTIVE;
					TWT_DEBUG printf( "        Capolinea!!! Sceso passeggero:  \e[1;34m%s\e[0m - # fermate: %d\n" , man->code_id , abs( man->id_discesa - man->id_salita ) );
					man->on_board = __GIM_NO;
					twt->num_passeggeri--;
				}
			}
		}
	}
	else {
		TWT_DEBUG printf( "    Items: %d - Num discese: %d\n" , last_ps , discese );
		for( _gim_int32 cnt = 0 ; cnt < discese ; cnt++ ) {
			oldest = 0;
			for( _gim_int32 lpsid = 1 ; ( ( lpsid <= last_ps ) && ( dec_id <= 0 ) ) ; lpsid++ ) {
				man = (_twt_man *)people->get_item( lpsid );
				if ( ( man->id_viaggio == vg ) && ( man->on_board == __GIM_YES ) ) {
					old = abs( fermata - man->id_salita );
					dec_id = man_decisione( lpsid );
					TWT_DEBUG printf("        ID fermata: %d - ID salita: %d - # fermate: %d\n" , fermata , man->id_salita , abs( fermata - man->id_salita ) );
					TWT_DEBUG printf("        ID: %d - Analisi passeggero:  %s - # fermate: %d - Perc_decisione: %d - Decisione: %s\n" , lpsid , man->code_id , abs( fermata - man->id_salita ) , man->perc_decisione , dec_id<=0?"NO":"YES" );
					if ( dec_id > 0 ) {
						oldest_id = lpsid;
						TWT_DEBUG printf("        The passenger wants to get off - ID: %d - Analisi passeggero:  %s - # fermate: %d\n" , lpsid , man->code_id , abs( fermata - man->id_salita ) );
					}
					else { 
						if ( ( old > oldest ) && ( man->on_board == __GIM_YES ) ) {
							oldest = old;
							oldest_id = lpsid;
							TWT_DEBUG printf("        Seraching for oldest - ID: %d - Analisi passeggero:  %s - # fermate: %d\n" , lpsid , man->code_id , abs( fermata- man->id_salita ) );
						}
					}
				}
				else {
					TWT_DEBUG printf(" -- Not same Travel or not on board! Current travel %1.1f - Passenger travel: %1.1f - On board %s - ID discesa: %d - %s\n" , vg , man->id_viaggio , man->on_board==__GIM_NO?"NO":"YES" , man->id_discesa , man->code_id );  
				}
			}
			TWT_DEBUG printf(" -- Out from the main cicle! ID: %d\n" , oldest_id );		
			if ( ( old != __UNKN ) || ( dec_id > 0 ) ) {
				
				if ( oldest_id > 0 ) {
					man = (_twt_man *)people->get_item( oldest_id );
					man->id_discesa = fermata;
					man->active = __NOT_ACTIVE;
					printf("        Sceso passeggero:  \e[1;34m%s\e[0m - # fermate: %d - Perc_decisione: %d - Decisione: %s\n" , man->code_id , abs( man->id_discesa - man->id_salita ) , man->perc_decisione , dec_id<=0?"NO":"YES" );
					TWT_DEBUG printf( "            On board: %d - CURRENT ID Viaggio %1.1f - ID Viaggio %1.1f - old: %d - oldest: %d - PS id: %d - Dec id: %d\n" , man->on_board , vg , man->id_viaggio , old , oldest , oldest_id , dec_id );
					man->on_board = __GIM_NO;
					twt->num_passeggeri--;
					dec_id = __UNKN;
				}				
				else {
					TWT_DEBUG printf( "\n    CURRENT ID Viaggio %1.1f - old: %d - oldest: %d - PS id: \e[1;31m%d\e[0m - Decision: %s (%d)\n" , vg , old , oldest , oldest_id , dec_id<=0?"NO":"YES" , dec_id );
					TWT_DEBUG printf("\e[1;31m    !!!Corrected index value!!!\n    He is still on board!!!\e[0m\n" );
					twt->errore = __GIM_ERROR;
				}
			}
			else {
				TWT_DEBUG printf( "\n    CURRENT ID Viaggio %1.1f - old: %d - oldest: %d - PS id: \e[1;31m%d\e[0m - Decision: %s (%d)\n" , vg , old , oldest , oldest_id , dec_id<=0?"NO":"YES" , dec_id  );
				TWT_DEBUG printf( "\e[1;31m    Errore in discesa passeggero\e[0m\n" );
				twt->errore = __GIM_ERROR;
			}
			
		}
	}
}



char *	rf_id_passeggero( void ) {
	_gim_Uint32	rnd = 0;
	mt->seed();
	rnd = mt->randInt();
	return cs->md5( (char *)&rnd , sizeof( _gim_Uint32 ) );
}




