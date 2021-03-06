#include "basic.h"
#include "types.h"
#include "decode.h"
#include <string.h>
#include <math.h>

#if 0
unsigned char *prog;
long *index_stack;
long stack[20];
char *time_buf;
long v, value;
long op1,op2;
int cond;
long n,*pn;
long timeout;
unsigned char alarm_flag;
unsigned char error_flag;


Str_program_point	far    programs[MAX_PRGS];
char 		far	    	*program_address[MAX_PRGS]; /*pointer to code*/
char    	 far   		pro_code[PROGRAMS_POOL_SIZE];
Uint 			    	code_length;


void Test_program(void)
{
	memcpy(&program_address[0],"TEST1",50);
}


void control_logic(void)
{
	U16_T i;
	Str_program_point *ptr;

	ptr = programs;	

		/* deal with exec_program roution per 1s */	
	//	convert_in();
		ptr = programs;
		for( i = 0; i < MAX_PRGS; i++, ptr++ )
		{
			if( ptr->bytes )
				if( program_address[i] )
				if(ptr->on_off)  // ptr->on_off		 
				{
					exec_program( i, program_address[i]);
				}
		}
	//	convert_out();


}


int exec_program(int current_prg, unsigned char *prog_code)
{
	Point p_var;
//	Point_Net point_net;
	int val1, val2, step;
	int nbytes;
	long *i_stack, *idecl_stack;
	int  ind, i, j;
	int id, len, nprog, nitem, lvar, ndeclare;
	char then_else;
	char ana_dig;
	char *return_pointer, *decl_prog, *p_buf, *p, *q;
	unsigned long r;
	unsigned char type_var;
	long value, v1, v2;
	unsigned char *local;
	int r_ind_remote;
//	Program_remote_points *r_remote, *remote_local_list;
//	int ind_remote_local_list;
	
	then_else /*= alarm_flag= error_flag */ = 0;
/*	prog = (unsigned char *)prog_code;
	if (called_program)
	 {
		if (*(prog+2+3)!=DECLARE)
			 return 1;
	 }
	else */
	 index_stack = stack;
	
	memcpy(&nbytes, prog, 2);
	prog += nbytes+2+3;
	memcpy(&nbytes, prog, 2);       /*LOCAL VARIABLES*/
	local = (prog+2);
	
	prog += 2 + nbytes;
	memcpy(&nbytes, prog, 2);
	prog += 2;
	p_buf = (char*)prog + nbytes;
	time_buf = (char*)prog;
	
//	memcpy(&ind_remote_local_list,prog+nbytes,2);
//	remote_local_list = (Program_remote_points*)(prog+nbytes+2);
	/* memcpy(remote_local_list,prog+nbytes+2,ind_remote_local_list*sizeof(Remote_local_list));*/

	while( (char*)prog < p_buf)
	{
		cond = (int)veval_exp( local);
		pn = (long *)(prog+1);
		if (cond)
		{
			if(*prog++)
			{
		//	 if(just_load) *pn = 0;
		//	 (*pn) += miliseclast_cur;
			}
			else
			{
			 *(prog-1) = 1;
			 *pn = 0;
			}
	 }
	 else
			if(*prog++)
			{
			 *(prog-1) = 0;
			 *pn = 0;
			}
			else
			{
		//	 if(just_load) *pn = 0;
		//	 (*pn) += miliseclast_cur;
			}
	 prog += 4;
 }

 prog = (unsigned char *)prog_code;
 p_buf = (char*)prog;
 memcpy(&nbytes, prog, 2);

// g_ind_remote_local_list = ind_remote_local_list;
// g_remote_local_list = remote_local_list;

 p_buf += 2;
 prog += 2;

 prog = prog + *(prog + nbytes + 1);

// alarm_at_all = OFF;
// ind_alarm_panel = 0;
// timeout = 0;
 while(*prog!=0xfe)
 {
	 if (timeout==8)
	 {
		programs[current_prg].errcode = 1;
		break;
	 }
	 lvar = 0;
	 if(!then_else)
	 {
		 if (*prog!=0x01)
		 {
				return -1;
		 }
		 prog++;			/* step over 01*/
		 prog += 2;
	 }
	 else
		 if (*prog==0x01)
				{
				 then_else = 0;
				 continue;
				}

	 switch (*prog++) {
			case ASSIGN:
			case ASSIGNAR:
			case ASSIGNARRAY_1:
			case ASSIGNARRAY_2:
			case STARTPRG:
			case OPEN:
			case ENABLEX:
			case STOP:
			case CLOSE:
			case DISABLEX:
								id = *(prog-1);
								if (id == ASSIGN || id == ASSIGNAR)
										 ana_dig=ANALOG;
								else
										 ana_dig=DIGITAL;

								if (*prog >= LOCAL_VARIABLE && *prog <= STRING_TYPE_ARRAY)
								{
											type_var = LOCAL;
											p = prog;
											prog++;
											prog += 2;
								}
								else
								  if (*prog == LOCAL_POINT_PRG)
								  {
										  prog++;
										  type_var = LOCAL_POINT_PRG;
										  p_var = *((Point *)prog);
										  prog += sizeof(Point);
								  }
								  else
								  {
									 /* if (*prog == REMOTE_POINT_PRG)
									  {
												prog++;
												type_var = REMOTE_POINT_PRG;
												point_net = *((Point_Net *)prog);
												prog += sizeof(Point_Net);
									  }	 */
								  }
								if ( id==OPEN )
								{
									 if (type_var == LOCAL_POINT_PRG)
									 {
									 	#if 0
										if ( p_var.point_type - 1 == GRP )
										{
											*((Point *)&localopenscreen) = p_var;
											localopenscreen.panel = Station_NUM-1;
											localopenscreen.network_number = 0xFFFF;      /*NetworkAddress;*/
											break;
										} 
										#endif
									 }
									/* if (type_var == REMOTE_POINT_PRG)
									 {
										if ( point_net.point_type - 1 == GRP )
										{
											localopenscreen = point_net;
									    break;
										}
									 }*/
								}
								if (id==STARTPRG || id==OPEN || id==ENABLEX) value = 1000L;
								if (id==STOP || id==CLOSE || id==DISABLEX) value = 0L;
								if (id==ASSIGN)
								{
									 value=veval_exp(local);
									 if (type_var == LOCAL)
									 {
									//		put_local_var(p,value,local);
									// tbd:
									}
								}
								else
								 if (id==ASSIGNARRAY_1)
								 {
										v2 = 0;
										v1 = 1;
										v2 = veval_exp(local);
										value=veval_exp(local);
									//	put_local_array(p,value,v1,v2/1000L,local);
									// tbd:
								 }
								 else
									if (id==ASSIGNARRAY_2)
									{
										v2 = 0;
										v1 = veval_exp(local);
										v2 = veval_exp(local);
										value=veval_exp(local);
									//	put_local_array(p,value,v1/1000L,v2/1000L,local);
										// tbd:
									}
									else
									{
									if( id==ASSIGNAR )
									{
											ana_dig = (int)(veval_exp(local)/1000)-1;
											value=veval_exp(local);
									}
									else
									{
									 if (type_var == LOCAL)
									 ;
									 // tbd:
									//		put_local_var(p,value,local);
									}
									}
								if (type_var == LOCAL_POINT_PRG)
								;
									// tbd:
									//	put_point_value( &p_var, &value, ana_dig, PROGR );
								break;
		
			case REM:
			case DIM:
			case INTEGER_TYPE:
			case BYTE_TYPE:
			case STRING_TYPE:
			case LONG_TYPE:
			case FLOAT_TYPE:
									len = *prog++;
									prog += len;
									break;
			case PRINT:
									break;
			case CLEARX:              /* clear all local variables to zero*/
/*
									for(ind=0;ind<MAX_VAR;ind++)
											local[ind]=0;
*/
									break;

			case ENDPRG:
									return 1;      /* end program*/
			case RETURN:
                  r = poplong();
									prog = (char *)r;
									break;
									break;
			case ON:
									nitem = veval_exp(local);
									if (nitem < 1 || nitem > *(prog+1))
											{
											 while(*prog!='\x1') prog++;
											 break;
											}
									if (*prog==GOSUB)   /*gosub*/
										 {
											return_pointer =  (char *)prog + 2 + *(prog+1)*2;
											pushlong((long)return_pointer);
										 }
									memcpy(&i, prog + 2 + (nitem-1)*2, 2);
									prog = (unsigned char *)p_buf + i - 2;
									break;
			case GOSUB:

									return_pointer =  (char*)prog + 2 ;
									memcpy(&i, prog, 2);
									prog = (unsigned char *)p_buf + i - 2;
									pushlong((long)return_pointer);
									break;

			case ON_ALARM:
									if (alarm_flag)
									{
										memcpy(&i, prog, 2);
										prog = (unsigned char *)p_buf + i - 2;
										alarm_flag=0;
									}
									else
									 	prog += 2;
									break;
			case ON_ERROR:
									if (error_flag)
									{
										memcpy(&i, prog, 2);
										prog = (unsigned char *)p_buf + i - 2;
										error_flag=0;
									}
									else
									 prog += 2;
									break;
			case GOTOIF:
			case GOTO:
									memcpy(&i, prog, 2);
									prog = (unsigned char *)p_buf + i - 2;
									break;
			case Alarm:
									break;
			case CALLB:
									break;
			case FOR:
									p = prog;
									prog += 3;
									val1 = veval_exp(local);
									val2 = veval_exp(local);
									step = veval_exp(local);
									if(val2>=val1)
									{
									 //put_local_var(p,val1,local);
									 // tbd:
									 prog += 2;
/*											interpret(); */
									}
									else
									{
									 memcpy(&lvar, prog, 2);
									 prog = p_buf + lvar - 2;
									}
									break;
			case NEXT:
								 {
									memcpy(&lvar, prog, 2);
									prog = p_buf + lvar - 2 + 4;
                  					p = prog;
									prog += 3;
									val1 = veval_exp(local);
									val2 = veval_exp(local);
									step = veval_exp(local);
									q = prog;
									prog = p;
									value = operand(NULL,local);    /*	veval_exp(local);*/
									value += step;
								//	put_local_var(p,value,local);
								// tbd:
									prog = q;
									if(value<=val2)
									{
									 prog += 2;
									}
									else
									{
									 memcpy(&lvar, prog, 2);
									 prog = p_buf + lvar - 2;
									}
								 }
								 break;
			case IF:
									then_else = 1;
									cond = veval_exp(local);
									if (cond)
									 {
										prog++; prog++;
									 }
									else
									 {
										prog = (unsigned char *)p_buf + *((int *)prog) -2;
										if( *prog == 0x01 || *prog == 0xFE)      /*TEST DACA EXISTA ELSE*/
											then_else = 0;
									 }
									break;
			case IFP:
									cond = veval_exp(local);
									if (cond)
									 if (!*prog++)
									 {
										*(prog-1) = 1;
										prog++; prog++;
									 }
									else
									 {
										prog = (unsigned char *)p_buf + *((int *)prog) -2;
									 }
									else
									 {
										*prog++ = 0;
										prog = (unsigned char *)p_buf + *((int *)prog) -2;
									 }

									then_else = 1;
									if( *prog == 0x01 || *prog == 0xFE)      /*TEST DACA EXISTA ELSE*/
										then_else = 0;
									break;
			case IFM:
									cond = veval_exp(local);
									if (!cond)
									 if (*prog++)
									 {
										*(prog-1) = 0;
										prog++; prog++;
									 }
									else
									 {
										prog = (unsigned char *)p_buf + *((int *)prog) -2;
									 }
									else
									 {
										*prog++ = 1;
										prog = (unsigned char *)p_buf + *((int *)prog) -2;
									 }
									then_else = 1;
									if( *prog == 0x01 || *prog == 0xFE)      /*TEST DACA EXISTA ELSE*/
										then_else = 0;
									break;
			case ELSE:
									prog++;
									prog = (unsigned char *)p_buf + *((int *)prog) -2;
									break;
			case WAIT:
							/*		return_pointer = (char *)prog-4;
									if (*prog==0xA1)
										 {
											memcpy(&r,++prog,4);
											prog += 4;
										 }
									else
										 {
											r = (unsigned long)veval_exp(local);
										 }

							    memcpy(&value,prog,4);
							    value += miliseclast_cur;
							    if (value/1000L >= r)
							    {
									 memset(prog,0,4);
									 *((int *)(p_buf + nbytes + 1))=0;
                   timeout = 0;
							    }
							    else
							    {
									 memcpy(prog,&value,4);
									 *((int *)(p_buf + nbytes + 1))=return_pointer-p_buf;
									 return 1;
							    }
							    prog += 4; */
							    break;
	 }
	}
}


long veval_exp(unsigned char *local)
{
 int i, m;
 char *p;
 long n;
 /* long timer;*/

 if (*prog >= LOCAL_VARIABLE && *prog <= REMOTE_POINT_PRG )
	push(operand(0,local));

 while( !isdelimit(*prog))         /* && code < )*/
 {
	switch (*prog++) {
		case PLUS:
							 push(pop() + pop());
							 break;
		case MINUS:
							 push(-pop() + pop());
							 break;
		case MINUSUNAR:
							 push(-pop());
							 break;
		case POW:
								 op2 = pop(); op1 = pop();
							 m = op2/1000L;
							 n = op1;
							 if(m>1)
							 {
								for(i=0;i<m-1;i++)
								 n = (n/1000L)*op1 + (n%1000L)*op1/1000L;
               }
							 push( n );
							 break;
		case MUL:
							 op2 = pop(); op1 = pop();
							 push( (op1/1000L)*op2 + (op1%1000L)*op2/1000L );
							 break;
		case DIV:
							 op2 = pop(); op1 = pop();
							 if(op2==0)
									push(1000L);
							 else
								 push( (op1/op2)*1000L + ((op1%op2)*1000L)/op2 );
							 break;
		case MOD:
							 op2 = pop(); op1 = pop();
							 if(op2==0)
									push(1000L);
							 else
							 {
								 op1 = op1%op2;
								 op1 /=1000L;
								 push( op1*1000L );
							 }
							 break;
		case XOR:
							 op2 = pop()/1000L; op1 = pop()/1000L;
							 push((op2 ^ op1)*1000L);
							 break;
		case OR:
							 op1 = pop(); op2 = pop();
               if( op1 || op2 )
								 push( 1000L );
               else
								 push( 0 );
							 break;
		case AND:
							 op1 = pop(); op2 = pop();
               if( op1 && op2 )
								 push( 1000L );
               else
								 push( 0 );
							 break;
		case NOT:
							 op1 = !pop();
							 push(op1);
							 break;
		case GT:
							 op2 = pop(); op1 = pop();
							 push(op1 > op2);
							 break;
		case GE:
							 op2 = pop();
							 push(pop() >= op2);
							 break;
		case LT:
							 op2 = pop(); op1 = pop();
							 push(op1 < op2);
							 break;
		case LE:
							 op2 = pop();
							 push(pop() <= op2);
							 break;
		case EQ:
							 push( pop() == pop() );
							 break;
		case NE:
							 push( pop() != pop() );
							 break;
		case ABS:
							 push(labs(pop()));
							 break;
		case LN:
/*
							 push((float)log(pop()));
*/
							 break;
		case LN_1:
/*
							 push((float)exp(pop()));
*/
							 break;
		case SQR:
/*
							 push((float)sqrt(pop()));
*/
							 break;
		case INT:
							 push( pop()/1000L * 1000L );
							 break;
		case SENSOR_ON:
							{
							 pop();
						//	 push( ( inputs[*(prog-3)].sen_on ) ? 1000L : 0L );
							 }
							 break;
		case SENSOR_OFF:
							{
							 pop();
						//	 push( ( inputs[*(prog-3)].sen_off ) ? 1000L:0L );
							 }
							 break;
		case INTERVAL:
						/*	if(just_load)
							{
							 n = (unsigned long)pop();
							 push(0);
							}
							else
							{
							 memcpy(&n,prog,4);
							 n -= miliseclast_cur;
							 if( n > 0 )
							 {
									pop();
									push(0);
							 }
							 else
							 {
									 if( n+miliseclast_cur == LONGTIMETEST )
									 {
										 n = (unsigned long)pop();
										 push(0);
									 }
									 else
									 {
										n = (unsigned long)pop();
										push(1);
									 }
								 }
							}
							memcpy(prog,&n,4);
							prog += 4;	*/
							break;
	 case TIME_ON:
								 pn = (long *)(time_buf+(*(int *)prog));
								 if( *((char *)pn - 1) )
									 push(*pn);
								 else
									 push(0);
								 prog += 2;
								 break;
	 case TIME_OFF:
								 pn = (long *)(time_buf+(*(int *)prog));
								 if( *((char *)pn - 1) )
									 push(0);
								 else
									 push(*pn);
								 prog += 2;
								 break;
	 case TIME_FORMAT:
							 break;
    case RUNTIME:
					/*		 i = (int)pop()/1000L;
               if(!i)
               {
									push(((long)miliseclast_cur)*1000l);
               }
               else
									push(0l); */
							 break;
	 case AVG:
							 {
								m = *prog++;
								value=0;
								for(i=0;i<m;i++)
									value += pop();
								push(value/m);
								break;
							 }
	 case MAX:
							 {
								m = *prog++;
								value=pop();
								for(i=0;i<m-1;i++)
									if((v=pop()) > value) value = v;
								push(value);
								break;
							 }
	 case MIN:
							 {
								m = *prog++;
								value=pop();
								for(i=0;i<m-1;i++)
									if((v=pop()) < value) value = v;
								push(value);
								break;
							 }
	 case CONPROP:
							 break;
	 case CONRATE:
							 break;
	 case CONRESET:
							 break;
	 case Tbl:
						 push(1);
						 break;
	 case WR_ON:
	 case WR_OFF:
						{
					/*	 i=pop()/1000;   // which time on

						 m = ora_current.dayofweek-1;	
						 
						 if (m<0) m = 6;
						 p =(char *)wr_times[(pop()/1000)-1][m].time;

						 if(*(prog-1)==WR_ON)
								 value = (long)p[4*(i-1)+1]*3600L + (long)p[4*(i-1)]*60L;
						 else
								 value = (long)p[4*(i-1)+3]*3600L + (long)p[4*(i-1)+2]*60L;
						 push(value*1000L);
						 break;	 */
           			 }	 
/*	case DOM:
						value = (ora_current.day)*1000L;
						push(value);
            break;
	case DOW:
						value = ora_current.dayofweek*1000L;
						push(value);
            break;
	case DOY:
						value = (ora_current.day_of_year+1)*1000L;
						push(value);
            break;
	case MOY:
						value = (ora_current.month+1)*1000L;
						push(value);
            break;	*/

	case POWER_LOSS:
						 push(0);
						 break;
	case SCANS:
						 push(1);    /* nr scanari pe secunda*/
						 break;
	case SUN:
						 push(0);
						 break;
	case MON:
						 push(1000);
						 break;
	case TUE:
						 push(2000);
						 break;
	case WED:
						 push(3000);
						 break;
	case THU:
						 push(4000);
						 break;
	case FRI:
						 push(5000);
						 break;
	case SAT:
						 push(6000);
						 break;
/*
						push((long)*(prog-1));
						break;
*/
	case JAN:
						 push(1000);
						 break;
	case FEB:
						 push(2000);
						 break;
	case MAR:
						 push(3000);
						 break;
	case APR:
						 push(4000);
						 break;
	case MAYM:
						 push(5000);
						 break;
	case JUN:
						 push(6000);
						 break;
	case JUL:
						 push(7000);
						 break;
	case AUG:
						 push(8000);
						 break;
	case SEP:
						 push(9000);
						 break;
	case OCT:
						 push(10000);
						 break;
	case NOV:
						 push(11000);
						 break;
	case DEC:
						 push(12000);
						 break;
/*	case TIME:
					 {
						value =  ora_current_sec;
						push(value * 1000L);
						break;
					 }	*/
	case USER_A:
					 push(1);
					 break;
	case USER_B:
					 push(0);
					 break;
	case UNACK:
					 push(0);
					 break;
	case INKEYD:
					 i = pop()/1000;   /* offset last char */
					 m = (int)(pop()/1000);   /* nr. of chars */
					 n = pop()/1000;          /* offset */
/*
					 if( n >= i )
						 push( -1000l );
					 else
						 push( inkey( local + n, m, i-n)*1000l );
*/
					 push( -1000l );
					 break;
	case ASSIGNARRAY:
					 if (*prog >= LOCAL_VARIABLE && *prog <= STRING_TYPE_ARRAY)    /* local var */
						push( ((long)*((int *)(prog+1)))*1000L );
					 prog += 3;
					 break;
	default:
							prog--;
							push(operand(0,local));
	}
 }
	if (*prog==0xFF) prog++;
	return pop();
}

long operand(char **buf,unsigned char *local)
{

	char *p;
	int num;
	
	value = 0;
	if (*prog >= LOCAL_VARIABLE && *prog <= BYTE_TYPE)    /* local var */
	{
	prog += 3;
	if(buf)
		*buf=0;
	return localvalue(prog-3, local);
	}
	
	if (*prog == LOCAL_POINT_PRG)
	{
	/*	if( (((Point *)(prog+1))->point_type)-1 == ARRAY )
	{
		++prog;
		get_ay_elem(&value, local);
	}
	else */
	{
		get_point_value( ( (Point *)(++prog) ), &value );
		prog += sizeof(Point);
	 }
	 	return value;              /* = read point */
	}
  #if 0
	if (*prog == REMOTE_POINT_PRG)
	{
	if( (((Point_Net *)(prog+1))->point_type)-1==ARRAY )
	{
	 ++prog;
	 p = prog;
	 prog += sizeof(Point_Net);
	 num = veval_exp(local,0)/1000L-1;
	 get_net_point_value( (Point_Net *)p, &value );
	}
	else
	{
		get_net_point_value( ( (Point_Net *)(++prog) ), &value );
		prog += sizeof( Point_Net );
	}
	
	return value;              /* = read point */
	}
 #endif
	if (*prog == CONST_VALUE_PRG)
	{
		prog += 5;
		if(buf)
			*buf=0;
		return *((long *)(prog-4));
	}
 	return 0;
}


void push(long value)
{
 *index_stack++ = value;
}


long pop(void)
{
 return (*(--index_stack));
}

void pushlong(unsigned long value)
{
 memcpy(index_stack++, &value, 4);
}


unsigned long poplong(void)
{
 unsigned long value;
 memcpy( &value, --index_stack, 4);
 return (value);
}

int isdelimit(char c)
{
 if (strchr( "\x1\xFF\xFE" , c) )
			return 1;
	else
			return 0;
}

long localvalue(unsigned char *p, unsigned char *local)
{
  long l;
  int i;
  i = *((int *)(p+1));
  switch(*p){
		case FLOAT_TYPE:
		case LONG_TYPE:
				l = *((long *)&local[i]);
				break;
		case INTEGER_TYPE:
					l = (long)(*((int *)&local[i]))*1000L;
					break;
		case BYTE_TYPE:
					l = (long)((signed char)local[i])*1000L;
					break;
  }
	return l;
}

int get_point_value( Point *point, long *val_ptr )
{

 	#if 0
		switch( point->point_type-1 )
		{
		 case OUT:
			sptr.pout = &outputs[point->number];
			if( !sptr.pout->digital_analog ) /* DIGITAL */
			{
				*val_ptr = sptr.pout->control ? 1000L:0L;
			}
			else
			{
				*val_ptr = sptr.pout->value;
			}
			break;
		 case IN:
			sptr.pin = &inputs[point->number];
			if( !sptr.pin->digital_analog )
			{
				*val_ptr = ( sptr.pin->control) ? 1000L : 0L;
			}
			else
			{
				*val_ptr = sptr.pin->value;
			}
			break;
		 case VAR:
			sptr.pvar = &vars[point->number];
			if( !sptr.pvar->digital_analog )
			{
				*val_ptr = sptr.pvar->control ? 1000L : 0L;
			}
			else
			{
				*val_ptr = sptr.pvar->value;
			}
			break;
		 case CON:
			*val_ptr = controllers[point->number].value;
			break;
		 case WR:
			*val_ptr = weekly_routines[point->number].value?1000L:0;
			break;
		 case AR:
			*val_ptr = annual_routines[point->number].value?1000L:0;
			break;
		 case PRG:
			*val_ptr = programs[point->number].on_off?1000L:0;
			break;
		 case AMON:
			*val_ptr = monitors[point->number].status?1000L:0;
			break;
		}
		return point->number;

	*val_ptr = 0;
	return -1;
	#endif
}

#endif
