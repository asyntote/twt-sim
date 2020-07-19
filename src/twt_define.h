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


	#define __PERC_EVASIONE		15.0	//	% di evasione
	#define	__CAPIENZA_MEZZO	120		//	Totale dei posti



	
	#include <unistd.h>
	#include <gim/gim.h>
	
	#define __ACTIVE		1
	#define	__NOT_ACTIVE	0
	
	#define	__LINEA			1
	
	#define	__RFID_TH_LO	10
	#define	__RFID_TH_HI	33
	
	#define	__MAIN_LOOP(a)	for( _gim_Uint8 vg = 1 ; ( (vg <= a ) && ( twt->errore == __GIM_OK ) ) ; vg++ )	
		
	#define	__INIT		"TWT Initialization!"	
	#define	__STAR		"The bus starts the service"
	#define	__CAPA		"Arrival at the bus terminus."
	#define	__CAPO		"Stop at the bus terminus."
	#define	__CAPP		"Departure from the bus terminus."
	#define	__VIAG		"Bus traveling."
	#define	__APPR		"Bus approaching the stop."
	#define	__FERM		"The bus stops. Doors opening."
	#define	__CHIU		"Doors closing. The bus leaves the stop."

	#define	__INIT_ST	-2		//	Inizialiazzazione
	#define	__STAR_ST	-1		//	Entrata in servizio
	#define	__CAPA_ST	0		//	Arrivo in Capolinea
	#define	__CAPO_ST	2		//	Sosta in Capolinea
	#define	__CAPP_ST	1		//	Partenza da Capolinea
	#define	__VIAG_ST	3		//	Viaggio
	#define	__APPR_ST	4		//	Approccio in fermata
	#define	__FERM_ST	5		//	Fermata
	#define	__CHIU_ST	6		//	Ciusura porte e partenza da fermata
	
	#define	__STAR_TM	0.5
	#define	__CAPA_TM	0.2		//	Arrivo in Capolinea
	#define	__CAPO_TM	1.0		//	Sosta in Capolinea
	#define	__CAPP_TM	0.2		//	Partenza da Capolinea
	#define	__VIAG_TM	0.5		//	Viaggio
	#define	__APPR_TM	0.2		//	Approccio in fermata
	#define	__FERM_TM	1.0		//	Fermata
	#define	__CHIU_TM	0.2		//	Ciusura porte e partenza da fermata
	
	
	#define PERC_EVASIONE		15.0	//	% di evasione

	#define	__CAPIENZA_MEZZO	120		//	Totale dei posti

//	COLOR_NC='\e[0m'
//	COLOR_RED='\e[0;31m'
//	COLOR_GREEN='\e[0;32m'


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
	#define __BSTOPS		( __DW_CAPO + 1 )		
	
	
	extern char	Linea1[][64];

	#define	__ANDATA		1
	#define	__RITORNO		2

	struct	_twt_st {
		_gim_flag	status;
		float		perc_evasione;
		_gim_Uint8	capienza;
		_gim_Uint32	num_passeggeri;
		_gim_Uint8	intensita;
		_gim_flag	ar;
		_gim_Uint8	fermata_corrente;
		float		arrivo_capolinea_sec;
		float		capolinea_sec;
		float		partenza_capolinea_sec;
		float		viaggio_sec;
		float		approccio_sec;
		float		fermata_sec;
		float		chporte_sec;
		_gim_flag	errore;
	};	
	
	#define	__MAX_PASS_UP		10
	#define	__MAX_PASS_DW		10
	
	#define __TH_DISCESA		6

	struct _twt_man {
		_gim_flag	type;
		_gim_Uint8	linea;
		_gim_flag	active;
		float	id_viaggio;
		_gim_Uint8	id_salita;
		_gim_flag	on_board;
		_gim_Uint8	id_discesa;
		_gim_Uint8	perc_decisione;
		_gim_flag	status;
		_gim_flag	optic_count;
		char		code_id[ GIM_MD5_SIZE ];
		_gim_flag	twt_str_code;
		_gim_flag	twt_mid_code;
		_gim_flag	twt_end_code;
	};
	
	#define	PEOPLE_NUMBER	5000
	
	#define	__MAX_FERMATE	25						//	per passeggero
	
	#define	__CROWD_HI		3
	#define	__CROWD_MD		2
	#define	__CROWD_LO		1
	#define	__CROWD_CONST	5
	
	#define __CURRENT_CROWD	__CROWD_HI

	extern	gim_obj 		* gim;
	extern	_gim_list		* people;
	extern	_twt_st			* twt;
	extern	_twt_man		* Tman;
	extern	_gim_checksum	* cs;
	extern	_gim_rand		* mt;
	
	
	_twt_man *		new_twt_man( void );
	const char *	get_state_name( _gim_flag st );
	void			twt_sleep( float sec );
	void 			viaggio( float vg );
	void			entrata_passeggero( void );
	void			uscita_passeggero( void );
	void 			ps_salita( _gim_int8 fermata , float vg );
	void 			ps_discesa( _gim_int8 fermata , float vg );
	char *			rf_id_passeggero( void );
	_gim_flag		man_decisione( _gim_int32 id );
	
	
#endif


