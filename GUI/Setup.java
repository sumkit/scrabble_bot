package scrabble_bot.GUI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import edu.cmu.cs.cs214.hw4.core.Player;

/**
 * Setup JPanel where users input players's names
 */
public class Setup extends JPanel {
	private static final long serialVersionUID = 6057724070732692168L;
	private static final String WELCOME = "Welcome to Scrabble with Stuff."+"\n "
			+ "Please enter 2-4 players's names.";
	private static final String ERROR = "You did not enter enough names."+"\n"
			+ "Please enter 2-4 players's names.";
    private static final int NUM_COLUMNS = 50;
    
	private final JFrame parentFrame;
	private JTextArea title;
	private JTextArea[] areas = new JTextArea[4];
	private JTextField[] names = new JTextField[4];
	private JButton next = new JButton("Play");

	/**
	 * Constructor for JPanel Setup
	 * @param frame is a JFrame object representing the parent frame that this panel will be inside of
	 */
	public Setup(JFrame frame) {
		this.parentFrame = frame;
		
		//Setup panel has Box Layout with components stacked on y axis
		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

		title = new JTextArea(Setup.WELCOME);
		title.setEditable(false);
		title.setLineWrap(true);
		title.setWrapStyleWord(true);
		this.add(title);

		//where user enters 2-4 players's names
		for(int i = 0; i < 4; i++) {
			this.areas[i] = new JTextArea("Player "+Integer.toString(i+1)+": ");
			this.areas[i].setEditable(false);
			names[i]=new JTextField(Setup.NUM_COLUMNS);
			this.add(this.areas[i]);
			this.add(names[i]);
		}	
		
		//next button to submit players's names
		next.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				toGame();
			}
		});	

		this.add(next);
		this.setVisible(true);
	}
	
	/**
	 * Transition from Setup to GamePanel JPanel.
	 */
	public void toGame() {
		//get names of Players
		List<Player> players = new ArrayList<Player>();
		for(JTextField n : names) {
			if(!(n.getText().isEmpty()))
				players.add(new Player(n.getText()));
		}
		//need to meet requirement of entering 2-4 players's names
		if(players.size() < 2)
			title.setText(Setup.ERROR);
		else {
			//transition from Setup to GamePanel panel
			try {
				parentFrame.remove(this);
				parentFrame.add(new GamePanel(players));
				
				//display the JFrame
				parentFrame.pack();
				parentFrame.setResizable(true);
				parentFrame.setVisible(true);
			} catch (FileNotFoundException e1) {
				e1.printStackTrace();
			}
		}
	}
	
	/**
	 * main method to start the Game
	 * @param args are the arguments
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				JFrame frame = new JFrame("Scrabble with Stuff");
				//add frame and set its closing operation
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
				//add panel to setup game and enter Players's names  
				frame.add(new Setup(frame));

				//display the JFrame
				frame.pack();
				frame.setResizable(true);
				frame.setVisible(true);
			}
		});	
	}
}
