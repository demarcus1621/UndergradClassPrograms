package com.ausoft;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UserController{
	UserView uView;
	RemoteDataAccess db;
	
	public UserController(UserView u, RemoteDataAccess dao){
		uView = u;
		db = dao;
		uView.btnSave.addActionListener(this);
		uView.btnLoad.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == uView.btnLoad){
			loadUserAndDisplay();
		}
		if(e.getSource() == uView.btnSave){
			saveUser();
		}
	}
	
	public void saveUser(){
		
	}
	
	public void loadUserAndDisplay(){
		
	}
}