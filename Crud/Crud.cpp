#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iomanip>
#include <clocale>

using namespace std;
using std::setlocale;

struct work
	{
		char DEPT_CODE[5], TAB_NUM[7], FIO[16], SALARY[8];
	} w;

struct record
	{
		char DOC_NUM[5], DAY[3], MONTH[3], YEAR[5], DEPT_CODE[5], SECT[2], TAB_NUM[7], REASON[5], PERCENT[5], TIME[4];
	} rec;

void work_input()
	{
		int check=0, isdata=0;
		ofstream iwork ("work_data.txt", ios::out | ios::binary | ios::app);
	    do
	    	{
				system ("cls");
	    		cout << "Enter data: ";
	    		check=0;
	    		strcpy(w.DEPT_CODE, "     ");
				strcpy(w.TAB_NUM, "       ");
				strcpy(w.FIO, "                ");
				
				isdata=0;
				do 
					{
						cout << "\nEnter department code: ";
						cin >> w.DEPT_CODE;
						
						if (atoi(w.DEPT_CODE)<1000 || atoi(w.DEPT_CODE)>9999)
							{
								cout << "Please enter 4 numbers of the department code!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter table number ";
						cin >> w.TAB_NUM;
						
						if (atoi(w.TAB_NUM)<100000 || atoi(w.TAB_NUM)>999999)
							{
								cout << "Please enter 6 numbers of the worker`s table number!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				cout << "Enter worker`s last name: ";
				cin >> w.FIO;
				
				isdata=0;
				do 
					{
						cout << "Enter salary: ";
						cin >> w.SALARY;
						
						if (atoi(w.SALARY)<0 || atoi(w.SALARY)>9999999)
							{
								cout << "Please enter an integer number - worker`s salary!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				iwork.write ((char*)&w, sizeof(w));
				cout << "Continue input?\n1 - yes\t0 - no\n";
				cin >> check;
			} while(check!=0);
		iwork.close();
	}

void work_edit()
	{
		int check=0, isdata=0, posich=0, confirm_change;
		char check_tab_num[7], check_fio[16];
		fstream ichange ("work_data.txt", ios::in | ios::out | ios::binary);
		if (!ichange)
			{
				system ("cls");
				cerr << "File can`t be opened!";
				exit(1);
	    	}
	    
	    isdata=0;
		do
	    	{
	    		isdata=0;
				do 
					{
						system ("cls");
						cout << "Enter the table number and worker`s last name to edit data: \n";
	    				cin >> check_tab_num >> check_fio;
					    ichange.read ((char*)&w, sizeof(w));
						while (!ichange.eof())
					    	{
			    				if (strcmp(check_tab_num, w.TAB_NUM)==0 && strcmp(check_fio, w.FIO)==0)
			    					{
										cout << "\nData for worker: ";
										cout << "\nDepartment code: " << w.DEPT_CODE;
										cout << "\nTable number: " << w.TAB_NUM;
										cout << "\nLast name:" << w.FIO;
										cout << "\nSalary:" << w.SALARY << endl;
			    						
			    						posich=ichange.tellp();
			    						isdata++;
			    						strcpy(w.DEPT_CODE, "     ");
										strcpy(w.TAB_NUM, "       ");
										strcpy(w.FIO, "                ");
										strcpy(w.SALARY, "        ");
										cout << "\nEnter new data: ";
							    		check=0;
							    		
							    		isdata=0;
										do 
											{
												cout << "\nEnter department code: ";
												cin >> w.DEPT_CODE;
												
												if (atoi(w.DEPT_CODE)<1000 || atoi(w.DEPT_CODE)>9999)
													{
														cout << "Please enter 4 numbers of the department code!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter table number ";
												cin >> w.TAB_NUM;
												
												if (atoi(w.TAB_NUM)<100000 || atoi(w.TAB_NUM)>999999)
													{
														cout << "Please enter 6 numbers of the worker`s table number!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										cout << "Enter worker`s last name: ";
										cin >> w.FIO;
										
										isdata=0;
										do 
											{
												cout << "Enter salary: ";
												cin >> w.SALARY;
												
												if (atoi(w.SALARY)<0 || atoi(w.SALARY)>9999999)
													{
														cout << "Please enter an integer number - worker`s salary!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
			    						
			    						cout << "\nConfirm changes?\n1 - yes\t0 - no\n";
										cin >> confirm_change;
										if (confirm_change==1)
											{
												ichange.seekp(posich-36, ios::beg);
												ichange.write ((char*)&w, sizeof(w));
											}
									}
								ichange.read ((char*)&w, sizeof(w));
							}
						if (isdata==0)
							{
								int to_menu;
								cout << "Check your input data!\n\nPress any key to return back to menu...";
								system ("pause");
								goto menu;
							}
						ichange.clear ();
						ichange.seekg (0, ios::beg);
						ichange.close ();
					} while(isdata==0);
				if (confirm_change==1) cout << "Record has been changed successfully!\nContinue editing?\n1 - yes\t0 - no\n";
				else cout << "Record has not been changed!\nContinue editing?\n1 - yes\t0 - no\n";
				cin >> check;
			} while(check!=0);
		menu:;
	}

void work_delete()
	{
		int check=0, isdata=0, posich=0, confirm_delete=0;
		char check_tab_num[7], check_fio[16];
		ifstream iwork ("work_data.txt", ios::in);
		if (!iwork)
	   		{
				cerr << "File can`t be opened!" << endl;
				exit(1);
	    	}
	    
	    isdata=0;
		do
	    	{
	    		system ("cls");
	    		isdata=0;
				do 
					{
						cout << "Enter the table number and worker`s last name to delete data: \n";
	    				cin >> check_tab_num >> check_fio;
	    				fstream idelete ("work_data.txt", ios::in | ios::out);
					    idelete.read ((char*)&w, sizeof(w));
						while (!idelete.eof())
					    	{
			    				if (strcmp(check_tab_num, w.TAB_NUM)==0 && strcmp(check_fio, w.FIO)==0)
			    					{
			    						isdata++;
			    						cout << "\nData for worker: ";
										cout << "\nDepartment code: " << w.DEPT_CODE;
										cout << "\nTable number: " << w.TAB_NUM;
										cout << "\nLast name:" << w.FIO;
										cout << "\nSalary:" << w.SALARY << endl;
										cout << "\nConfirm deleting?\n1 - yes\t0 - no\n";
										cin >> confirm_delete;
			    						
			    						if (confirm_delete==1)
				    						{
				    							posich=idelete.tellp();
				    							strcpy(w.DEPT_CODE, "     ");
												strcpy(w.TAB_NUM, "       ");
												strcpy(w.FIO, "                ");
												strcpy(w.SALARY, "        ");
									    		idelete.seekp(posich-36, ios::beg);
												idelete.write ((char*)&w, sizeof(w));
											}
									}
								idelete.read ((char*)&w, sizeof(w));
							}
						if (isdata==0)
							{
								cout << "Check your input data!\n\nPress any key to return back to menu...";
								system ("pause");
								goto menu;
							}
						idelete.clear ();
						idelete.seekg (0, ios::beg);
						idelete.close ();
					} while(isdata==0);
				if (confirm_delete==1) cout << "Record has been deleted successfully!\nContinue deleting?\n1 - yes\t0 - no\n";
				else cout << "Record has not been deleted!\nContinue deleting?\n1 - yes\t0 - no\n";
				cin >> check;
			} while(check!=0);
		menu:;
	}

void work_display()
	{
		int check;
		ifstream idisplay ("work_data.txt", ios::in | ios::binary);
		if (!idisplay)
	   		{
				cerr << "File can`t be opened!" << endl;
				exit(1);
	    	}
	    do 
			{
				system ("cls");
				cout << "\nWorkers data: ";
				cout << "\n______________________________________________________________________________________";
				cout << "\n| Department code | Table number |      Worker`s last name      |       Salary       |";
				cout << "\n|_________________|______________|______________________________|____________________|";
				idisplay.read ((char*)&w, sizeof(w));
				while (!idisplay.eof())
					{
						if (strcmp(w.DEPT_CODE, "                                    ")!=0) cout << "\n|" << setw(17) << w.DEPT_CODE << "|" << setw(14) << w.TAB_NUM << "|" << setw(30) << w.FIO << "|" << setw(20) << w.SALARY << "|";
						idisplay.read ((char*)&w, sizeof(w));
					}
				cout << "\n|_________________|______________|______________________________|____________________|";
	    		idisplay.clear ();
				idisplay.seekg (0, ios::beg);
				cout << "\n\nContinue output?\n1 - yes\t0 - no\n";
				cin >> check;
			} while (check!=0);
		idisplay.close ();
	}

void records_input()
	{
		int check=0, isdata=0;
		ofstream irec ("recs_data.txt", ios::out | ios::binary | ios::app);
	    do
	    	{
				system ("cls");
	    		cout << "Enter data: ";
	    		check=0;
	    		strcpy(rec.DOC_NUM, "     ");
	    		strcpy(rec.DAY, "   ");
				strcpy(rec.MONTH, "   ");
				strcpy(rec.YEAR, "     ");
				strcpy(rec.DEPT_CODE, "     ");
				strcpy(rec.SECT, "  ");
				strcpy(rec.TAB_NUM, "       ");
				strcpy(rec.REASON, "     ");
				strcpy(rec.PERCENT, "     ");
				strcpy(rec.TIME, "    ");
				
				isdata=0;
				do 
					{
						cout << "\nEnter document number:";
						cin >> rec.DOC_NUM;
						
						if (atoi(rec.DOC_NUM)<1 || atoi(rec.DOC_NUM)>9999)
							{
								cout << "Document number can be only 1 to 9999!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "\nEnter date:\nEnter day: ";
						cin >> rec.DAY;
						
						if (atoi(rec.DAY)<1 || atoi(rec.DAY)>31)
							{
								cout << "Day can be only 1 to 31!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter month: ";
						cin >> rec.MONTH;
						
						if (atoi(rec.MONTH)<1 || atoi(rec.MONTH)>12)
							{
								cout << "Month can be only 1 to 12!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter year: ";
						cin >> rec.YEAR;
						
						if (atoi(rec.YEAR)<1980 || atoi(rec.YEAR)>2020)
							{
								cout << "Year can be only 1980 to 2020!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
					
				isdata=0;
				do 
					{
						cout << "Enter department code: ";
						cin >> rec.DEPT_CODE;
						ifstream idept ("work_data.txt", ios::in | ios::binary);
						if (!idept)
					   		{
								cerr << "File can`t be opened!\n" << endl;
								exit(1);
					    	}
					    idept.read ((char*)&w, sizeof(w));
						while (!idept.eof())
					    	{
			    				if (strcmp(rec.DEPT_CODE, w.DEPT_CODE)==0) isdata++;
								idept.read ((char*)&w, sizeof(w));
							}
						if (isdata==0) cout << "There is no department with this code!\n";
						idept.clear ();
						idept.seekg (0, ios::beg);
						idept.close ();
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter section number: ";
						cin >> rec.SECT;
						
						if (atoi(rec.SECT)<1 || atoi(rec.SECT)>9)
							{
								cout << "Section number can be only 1 to 9!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter table number: ";
						cin >> rec.TAB_NUM;
						
						ifstream iwork ("work_data.txt", ios::in | ios::binary);
						if (!iwork)
					   		{
								cerr << "File can`t be opened!\n" << endl;
								exit(1);
					    	}
					    iwork.read ((char*)&w, sizeof(w));
						while (!iwork.eof())
					    	{
			    				if (strcmp(rec.TAB_NUM, w.TAB_NUM)==0) isdata++;
								iwork.read ((char*)&w, sizeof(w));
							}
						if (isdata==0) cout << "There is no worker with this table number!\n";
						iwork.clear ();
						iwork.seekg (0, ios::beg);
						iwork.close ();
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter code of reason of downtime: ";
						cin >> rec.REASON;
						
						if (atoi(rec.REASON)<1000 || atoi(rec.REASON)>9999)
							{
								cout << "Please enter the code of reason of downtime correctly!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter percent of salary to pay back: ";
						cin >> rec.PERCENT;
						
						if (atoi(rec.PERCENT)<0 || atoi(rec.PERCENT)>100)
							{
								cout << "Percent can be only 0 to 100!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				isdata=0;
				do 
					{
						cout << "Enter time of downtime (in minutes): ";
						cin >> rec.TIME;
						
						if (atoi(rec.TIME)<0 || atoi(rec.TIME)>999)
							{
								cout << "Time can be only 0 to 999!\n";
								isdata=0;
							}
						else isdata=1;
					} while(isdata==0);
				
				irec.write ((char*)&rec, sizeof(rec));
				cout << "Continue input?\n1 - yes\t0 - no\n";
				cin >> check;
			} while(check!=0);
		irec.close();
	}

void records_edit()
	{
		int check=0, isdata=0, posich=0, confirm_change;
		char check_day[3], check_month[3], check_year[5], check_doc_num[5];
		fstream ichange ("recs_data.txt", ios::in | ios::out | ios::binary);
		if (!ichange)
			{
				system ("cls");
				cerr << "File can`t be opened!";
				exit(1);
	    	}
	    
	    isdata=0;
		do
	    	{
	    		isdata=0;
				do 
					{
						system ("cls");
						cout << "Enter the document number and date to edit data: \n";
	    				cin >> check_doc_num >> check_day >> check_month >> check_year;
					    ichange.read ((char*)&rec, sizeof(rec));
						while (!ichange.eof())
					    	{
			    				if (strcmp(check_day, rec.DAY)==0 && strcmp(check_month, rec.MONTH)==0 && strcmp(check_year, rec.YEAR)==0 && strcmp(check_doc_num, rec.DOC_NUM)==0)
			    					{
										cout << "\nData for record: ";
										cout << "\nDocument number: " << rec.DOC_NUM;
										cout << "\nDate: " << rec.DAY << "/" << rec.MONTH << "/" << rec.YEAR;
			    						cout << "\nDepartment code: " << rec.DEPT_CODE;
			    						cout << "\nSection code: " << rec.SECT;
										cout << "\nTable number: " << rec.TAB_NUM;
										cout << "\nReason of downtime code: " << rec.REASON;
										cout << "\nPercent of salary to pay back: " << rec.PERCENT;
										cout << "\nTime of downtime (in minutes): " << rec.TIME << endl;
			    						
			    						posich=ichange.tellp();
			    						isdata++;
			    						strcpy(rec.DOC_NUM, "     ");
							    		strcpy(rec.DAY, "   ");
										strcpy(rec.MONTH, "   ");
										strcpy(rec.YEAR, "     ");
										strcpy(rec.DEPT_CODE, "     ");
										strcpy(rec.SECT, "  ");
										strcpy(rec.TAB_NUM, "       ");
										strcpy(rec.REASON, "     ");
										strcpy(rec.PERCENT, "     ");
										strcpy(rec.TIME, "    ");
										cout << "\nEnter new data: ";
							    		check=0;
							    		
							    		isdata=0;
										do 
											{
												cout << "\nEnter document number:";
												cin >> rec.DOC_NUM;
												
												if (atoi(rec.DOC_NUM)<1 || atoi(rec.DOC_NUM)>9999)
													{
														cout << "Document number can be only 1 to 9999!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "\nEnter date:\nEnter day: ";
												cin >> rec.DAY;
												
												if (atoi(rec.DAY)<1 || atoi(rec.DAY)>31)
													{
														cout << "Day can be only 1 to 31!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter month: ";
												cin >> rec.MONTH;
												
												if (atoi(rec.MONTH)<1 || atoi(rec.MONTH)>12)
													{
														cout << "Month can be only 1 to 12!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter year: ";
												cin >> rec.YEAR;
												
												if (atoi(rec.YEAR)<1980 || atoi(rec.YEAR)>2020)
													{
														cout << "Year can be only 1980 to 2020!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
											
										isdata=0;
										do 
											{
												cout << "Enter department code: ";
												cin >> rec.DEPT_CODE;
												ifstream idept ("work_data.txt", ios::in | ios::binary);
												if (!idept)
											   		{
														cerr << "File can`t be opened!\n" << endl;
														exit(1);
											    	}
											    idept.read ((char*)&w, sizeof(w));
												while (!idept.eof())
											    	{
									    				if (strcmp(rec.DEPT_CODE, w.DEPT_CODE)==0) isdata++;
														idept.read ((char*)&w, sizeof(w));
													}
												if (isdata==0) cout << "There is no department with this code!\n";
												idept.clear ();
												idept.seekg (0, ios::beg);
												idept.close ();
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter section number: ";
												cin >> rec.SECT;
												
												if (atoi(rec.SECT)<1 || atoi(rec.SECT)>9)
													{
														cout << "Section number can be only 1 to 9!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter table number: ";
												cin >> rec.TAB_NUM;
												
												ifstream iwork ("work_data.txt", ios::in | ios::binary);
												if (!iwork)
											   		{
														cerr << "File can`t be opened!\n" << endl;
														exit(1);
											    	}
											    iwork.read ((char*)&w, sizeof(w));
												while (!iwork.eof())
											    	{
									    				if (strcmp(rec.TAB_NUM, w.TAB_NUM)==0) isdata++;
														iwork.read ((char*)&w, sizeof(w));
													}
												if (isdata==0) cout << "There is no worker with this table number!\n";
												iwork.clear ();
												iwork.seekg (0, ios::beg);
												iwork.close ();
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter code of reason of downtime: ";
												cin >> rec.REASON;
												
												if (atoi(rec.REASON)<1000 || atoi(rec.REASON)>9999)
													{
														cout << "Please enter the code of reason of downtime correctly!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter percent of salary to pay back: ";
												cin >> rec.PERCENT;
												
												if (atoi(rec.PERCENT)<0 || atoi(rec.PERCENT)>100)
													{
														cout << "Percent can be only 0 to 100!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
										isdata=0;
										do 
											{
												cout << "Enter time of downtime (in minutes): ";
												cin >> rec.TIME;
												
												if (atoi(rec.TIME)<0 || atoi(rec.TIME)>999)
													{
														cout << "Time can be only 0 to 999!\n";
														isdata=0;
													}
												else isdata=1;
											} while(isdata==0);
										
			    						cout << "\nConfirm changes?\n1 - yes\t0 - no\n";
										cin >> confirm_change;
										if (confirm_change==1)
											{
												ichange.seekp(posich-44, ios::beg);
												ichange.write ((char*)&rec, sizeof(rec));
											}
									}
								ichange.read ((char*)&rec, sizeof(rec));
							}
						if (isdata==0)
							{
								int to_menu;
								cout << "Check your input data!\n\nPress any key to return back to menu...";
								system ("pause");
								goto menu;
							}
						ichange.clear ();
						ichange.seekg (0, ios::beg);
						ichange.close ();
					} while(isdata==0);
				if (confirm_change==1) cout << "Record has been changed successfully!\nContinue editing?\n1 - yes\t0 - no\n";
				else cout << "Record has not been changed!\nContinue editing?\n1 - yes\t0 - no\n";
				cin >> check;
			} while(check!=0);
		menu:;
	}

void records_delete()
	{
		int check=0, isdata=0, posich=0, confirm_delete=0;
		char check_day[3], check_month[3], check_year[5], check_doc_num[5];
		ifstream iwork ("recs_data.txt", ios::in);
		if (!iwork)
	   		{
				cerr << "File can`t be opened!" << endl;
				exit(1);
	    	}
	    
	    isdata=0;
		do
	    	{
	    		system ("cls");
	    		isdata=0;
				do 
					{
						cout << "Enter the document number and date to delete data: \n";
	    				cin >> check_doc_num >> check_day >> check_month >> check_year;
	    				fstream idelete ("recs_data.txt", ios::in | ios::out);
					    idelete.read ((char*)&rec, sizeof(rec));
						while (!idelete.eof())
					    	{
			    				if (strcmp(check_day, rec.DAY)==0 && strcmp(check_month, rec.MONTH)==0 && strcmp(check_year, rec.YEAR)==0 && strcmp(check_doc_num, rec.DOC_NUM)==0)
			    					{
			    						isdata++;
			    						cout << "\nData for record: ";
										cout << "\nDocument number: " << rec.DOC_NUM;
										cout << "\nDate: " << rec.DAY << "/" << rec.MONTH << "/" << rec.YEAR;
			    						cout << "\nDepartment code: " << rec.DEPT_CODE;
			    						cout << "\nSection code: " << rec.SECT;
										cout << "\nTable number: " << rec.TAB_NUM;
										cout << "\nReason of downtime code: " << rec.REASON;
										cout << "\nPercent of salary to pay back: " << rec.PERCENT;
										cout << "\nTime of downtime (in minutes): " << rec.TIME << endl;
										cout << "\nConfirm deleting?\n1 - yes\t0 - no\n";
										cin >> confirm_delete;
			    						
			    						if (confirm_delete==1)
				    						{
				    							posich=idelete.tellp();
				    							strcpy(rec.DOC_NUM, "     ");
									    		strcpy(rec.DAY, "   ");
												strcpy(rec.MONTH, "   ");
												strcpy(rec.YEAR, "     ");
												strcpy(rec.DEPT_CODE, "     ");
												strcpy(rec.SECT, "  ");
												strcpy(rec.TAB_NUM, "       ");
												strcpy(rec.REASON, "     ");
												strcpy(rec.PERCENT, "     ");
												strcpy(rec.TIME, "    ");
									    		idelete.seekp(posich-44, ios::beg);
												idelete.write ((char*)&rec, sizeof(rec));
											}
									}
								idelete.read ((char*)&rec, sizeof(rec));
							}
						if (isdata==0)
							{
								cout << "Check your input data!\n\nPress any key to return back to menu...";
								system ("pause");
								goto menu;
							}
						idelete.clear ();
						idelete.seekg (0, ios::beg);
						idelete.close ();
					} while(isdata==0);
				if (confirm_delete==1) cout << "Record has been deleted successfully!\nContinue deleting?\n1 - yes\t0 - no\n";
				else cout << "Record has not been deleted!\nContinue deleting?\n1 - yes\t0 - no\n";
				cin >> check;
			} while(check!=0);
		menu:;
	}

void records_display()
	{
		int check;
		ifstream idisplay ("recs_data.txt", ios::in | ios::binary);
		if (!idisplay)
	   		{
				cerr << "File can`t be opened!" << endl;
				exit(1);
	    	}
	    do 
			{
				system ("cls");
				cout << "\nRecords data: ";
				cout << "\n________________________________________________________________________________________________________________________";
				cout << "\n|Doc No|    Date    | Department code | Section | Table number |Reason of downtime|Percent to pay back|Time of downtime|";
				cout << "\n|______|____________|_________________|_________|______________|__________________|___________________|________________|";
				idisplay.read ((char*)&rec, sizeof(rec));
				while (!idisplay.eof())
					{
						if (strcmp(rec.DOC_NUM, "                                            ")!=0) cout << "\n|" << setw(6) << rec.DOC_NUM << "| " << setw(2) << rec.DAY << "/" << setw(2) << rec.MONTH << "/" << setw(4) << rec.YEAR << " |" << setw(17) << rec.DEPT_CODE << "|" << setw(9) << rec.SECT << "|" << setw(14) << rec.TAB_NUM << "|" << setw(18) << rec.REASON << "|" << setw(19) << rec.PERCENT << "|" << setw(16) << rec.TIME << "|";
						idisplay.read ((char*)&rec, sizeof(rec));
					}
				cout << "\n|______|____________|_________________|_________|______________|__________________|___________________|________________|";
	    		idisplay.clear ();
				idisplay.seekg (0, ios::beg);
				cout << "\n\nContinue output?\n1 - yes\t0 - no\n";
				cin >> check;
			} while (check!=0);
		idisplay.close ();
	}

int main()
	{
		menu:
		int choice;
		do
			{
				system ("cls");
				cout << "Menu:";
				cout << "\n0 - Exit";
				cout << "\n1 - Workers data";
				cout << "\n2 - Records data\n";
				cin >> choice;
				switch (choice)
					{
						case 0: exit(1);
						case 1: goto work_data;
						case 2: goto records_data;
						default: break;
					}
			} while (choice!=0);
		
		work_data:
		do
			{
				system ("cls");
				cout << "Workers data:";
				cout << "\n0 - Back to menu";
				cout << "\n1 - Add record";
				cout << "\n2 - Edit record";
				cout << "\n3 - Delete record";
				cout << "\n4 - Display workers data\n";
				cin >> choice;
				switch (choice)
					{
						case 0: goto menu;
						case 1: work_input(); break;
						case 2: work_edit(); break;
						case 3: work_delete(); break;
						case 4: work_display(); break;
						default: break;
					}
			} while (choice!=0);
		
		records_data:
		do
			{
				system ("cls");
				cout << "Records data:";
				cout << "\n0 - Back to menu";
				cout << "\n1 - Add record";
				cout << "\n2 - Edit record";
				cout << "\n3 - Delete record";
				cout << "\n4 - Display records data\n";
				cin >> choice;
				switch (choice)
					{
						case 0: goto menu;
						case 1: records_input(); break;
						case 2: records_edit(); break;
						case 3: records_delete(); break;
						case 4: records_display(); break;
						default: break;
					}
			} while (choice!=0);
	}
