#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SETBIT(WORD,BITPOS)	                        WORD|=(1<<BITPOS)
#define CLRBIT(WORD,BITPOS)	                        WORD&=~(1<<BITPOS)
#define WRITEBIT(WORD,BITPOS,BITVAL)	              WORD=(WORD&(~(1<<BITPOS)))|(BITVAL<<BITPOS)
#define CPLBIT(WORD,BITPOS)	                        WORD^=1<<BITPOS
#define	READBIT(WORD,BITPOS)	                      (WORD>>BITPOS)&1
#define	WRITE2BIT(WORD,STARTBITPOS,BITVAL)	        WORD=((WORD&~(0x03<<STARTBITPOS))|(BITVAL<<STARTBITPOS))
#define WRITEBYTE(WORD,STARTBITPOS,BYTE)	          WORD=((WORD&(~(0xff<<STARTBITPOS)))|(BYTE<<STARTBITPOS))
#define	READBYTE(WORD,STARTBITPOS)	                ((WORD>>STARTBITPOS)&0xff)
#define	WRITENIBBLE(WORD,STARTBITPOS,NIBBLE)	      WORD=((WORD&(~(0xf<<STARTBITPOS)))|(NIBBLE<<STARTBITPOS))
#define	READNIBBLE(WORD,STARTBITPOS)	              ((WORD>>STARTBITPOS)&0xf)
#define READWRITEBIT(WORD,WBITPOS,RBITPOS)	        WORD=((WORD&(~(1<<WBITPOS)))|(((WORD>>RBITPOS)&1)<<WBITPOS))
#define READWRITEBIT2(DWORD,WBITPOS,SWORD,RBITPOS)	DWORD=((DWORD&(~(1<<WBITPOS)))|(((SWORD>>RBITPOS)&1)<<WBITPOS))
#define SSETBIT(WORD,BITPOS)												WORD=(1<<BITPOS)
#define	SCLRBIT(WORD,BITPOS)												SSETBIT(WORD,BITPOS)
#define CFGPIN(WORD,PIN,FUNC) 							        WORD=((PIN<16) ? \
																			 ((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))): \
																			 ((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));

#endif
