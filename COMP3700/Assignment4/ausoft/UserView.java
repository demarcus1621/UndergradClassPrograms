package com.ausoft;

import javax.swing.*;
import java.awt.*;

public class UserView{

	public JTextField txtName = new JTextField(30);
	public JTextField txtAddress = new JTextField(30);
	public JTextField txtUsername = new JTextField(30);
	public JTextField txtPassword = new JTextField(30);
	public JTextField txtRole = new JTextField(5);
	
	public JButton btnLoad = new JButton("Load");
	public JButton btnSave = new JButton("Save");
	
	public UserView(){
		this.setTitle("User Database");
		this.setSize(new Dimension(600,300));
		this.getContentPane().setLayout(new BoxLayout(this.getContentPane(), BoxLayout.PAGE_AXIS));
		
		JPanel line1 = new JPanel();
		line1.add(new JLabel("Name"));
		line1.add(txtName);
		this.getContentPane().add(line1);
		
		JPanel line2 = new JPanel();
		line2.add(new JLabel("Address"));
		line2.add(txtAddress);
		this.getContentPane().add(line2);
		
		JPanel line3 = new JPanel();
		line3.add(new JLabel("Username"));
		line3.add(txtUsername);
		this.getContentPane().add(line3);
		
		JPanel line4 = new JPanel();
		line4.add(new JLabel("Password"));
		line4.add(txtPassword);
		this.getContentPane().add(line4);
		
		JPanel line5 = new JPanel();
		line5.add(new JLabel("Role"));
		line5.add(txtRole);
		this.getContentPane().add(line5);
		
		JPanel buttonPanel = new JPanel();
		buttonPanel.add(btnLoad);
		buttonPanel.add(btnSave);
		this.getContentPane().add(buttonPanel);
	}