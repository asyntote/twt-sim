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
	
	enum _acq_items_status_enum {
						//	PRIMO PASSAGGIO			CONDIZIONE OTTICO	CONDIZIONE RFID		PASSAGGIO INTERMEDIO	FINALE			
		"P1" = 1;		//	Lettura completa		OTTICO:	OK			RFID:	OK			/						P1	
		"P2",			//	Lettura completa		OTTICO:	OK			RFID:	NOT OK		/						P2,P1.3
		"E1",			//	Lettura parziale		OTTICO:	NOT OK		RFID:	OK			E1.1,E1.2,E1.3,E1.4		P1.1,P1.2,P1.3,N
		"E1.1",			//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/						P1.1
		"E1.2",			//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/						P1.2
		"E1.3",			//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/						P1.3
		"E1.4"			//	Lettura intermedia		OTTICO:	NOT OK		RFID:	OK			/						N
		"P1.1",			//	marcatura finale		OTTICO:	OK			RFID:	OK			E1.1
		"P1.2",			//	marcatura finale		OTTICO:	OK			RFID:	OK			E1.2
		"P1.3",			//	marcatura finale		OTTICO:	OK			RFID:	OK			E1.3
		"N",			//	marcatura finale		OTTICO:	NOT OK		RFID:	NOT OK		E1.4
	};
	
#endif


