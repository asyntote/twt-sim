/***************************************************************************
 *            twt_define.h
 *
 *  Sat June 20 22:12:35 2020
 *  Copyright  2020  Danilo
 *  <user@host>
 ****************************************************************************/
/*
 * twt_define.h
 *
 * Copyright (C) 2020 - Danilo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef	__TWT_DEFINE__
	#define	__TWT_DEFINE__
	
	#include <unistd.h>
	#include <gim/gim_checksum.h>
		
	#define __ACTIVE		1
	#define	__NOT_ACTIVE	0

		
	#define	__INIT		"Inizializzazione"	
	#define	__CAPO		"Capolinea"
	#define	__VIAG		"Viaggio"
	#define	__APPR		"Approccio"
	#define	__FERM		"In fermata"
	#define	__CHIU		"Chiusura porte"

	#define	__INIT_ST	-1
	#define	__CAPA_ST	0
	#define	__CAPO_ST	2
	#define	__CAPP_ST	1
	#define	__VIAG_ST	3
	#define	__APPR_ST	4
	#define	__FERM_ST	5
	#define	__CHIU_ST	6


	enum _man_status {
		__UNKN = -1,
		__UNDIFINED,
		__PAGANTE,
		__NON_PAGANTE,
		__FAMIGLIA,
		__AUTISTA,
	};

	enum _acq_items_status_enum {
		//	twt_str_code		PRIMO PASSAGGIO			CONDIZIONE OTTICO	CONDIZIONE RFID		twt_		FINALE		
		_UN = -1,			//	Undefined
		_P1 = 1,			//	Lettura completa		OTTICO:	OK			RFID:	OK			/							_P1	
		_P2,				//	Lettura completa		OTTICO:	OK			RFID:	NOT OK		/							_P2,_P1_3
		_E1,				//	Lettura parziale		OTTICO:	NOT OK		RFID:	OK			_E1_1,_E1_2,_E1_3,_E1_4		_P1_1,_P1_2,P1_3,_N
		_E1_1,				//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/							_P1_1
		_E1_2,				//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/							_P1_2
		_E1_3,				//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/							_P1_3
		_E1_4,				//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/							_N
		_P1_1,				//	marcatura finale		OTTICO:	OK			RFID:	OK			_E1_1
		_P1_2,				//	marcatura finale		OTTICO:	OK			RFID:	OK			_E1_2
		_P1_3,				//	marcatura finale		OTTICO:	OK			RFID:	OK			_E1_3
		_N					//	marcatura finale		OTTICO:	NOT OK		RFID:	NOT OK		_E1_4
	};
	
	
	#define	__UP_CAPO		0
	#define	__DW_CAPO		52
	
	
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


	struct	_twt_st {
		_gim_flag	status;
		_gim_Uint8	perc_non_paganti;
		_gim_Uint8	capienza;
		_gim_Uint8	intensita;
		_gim_Uint8	fermata_corrente;
		_gim_Uint8	viaggio_sec;
		_gim_Uint8	approccio_sec;
		_gim_Uint8	chporte_sec;
		_gim_Uint8	capolinea_sec;
		_gim_flag	errore;
	};	
	
	
	#define	__MAX_PASS_UP		10
	#define	__MAX_PASS_DW		10

	struct _twt_man {
		_gim_flag	type;
		_gim_Uint8	linea;
		_gim_flag	active;
		_gim_Uint8	id_salita;
		_gim_flag	on_board;
		_gim_Uint8	id_discesa;
		_gim_flag	status;
		char		code_id[ GIM_MD5_SIZE ];
		_gim_flag	twt_str_code;
		_gim_flag	twt_mid_code;
		_gim_flag	twt_end_code;
	};
	
	#define	PEOPLE_NUMBER	5000
	
	extern _gim_list	Passeggeri;
	
	_twt_man *	new_twt_man( gim_obj * gim );
	
#endif


