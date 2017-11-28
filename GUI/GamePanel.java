package scrabble_bot.GUI;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import edu.cmu.cs.cs214.hw4.core.Game;
import edu.cmu.cs.cs214.hw4.core.Move;
import edu.cmu.cs.cs214.hw4.core.Player;
import edu.cmu.cs.cs214.hw4.core.SpecialTile;
import edu.cmu.cs.cs214.hw4.core.Square;
import edu.cmu.cs.cs214.hw4.core.Tile;
/**
 * GamePanel is where the board is housed and moves are made. After Setup.
 *
 */
public class GamePanel extends JPanel {
	private static final String SELECTTILE = "Please select a Tile to play first.";
	private static final String INVALIDMOVE = "This is an invalid move. Please try again.";
	private static final String CANNOTAFFORD = "You cannot afford this Special Tile. Please select a different one.";
	private String instructions;
	private Tile currentTile;
	private List<Tile> move;
	private Game g;

	/**
	 * input from C++ after 1 turn: 
	 * - currPlayer
	 * - tiles (in order, including those already on the board)
	 * - start and end coordinates 
	 */

	//for the board
	private JTextArea top;
	private JPanel boardPanel,buttonPanel, tilePanel, specialPanel;
	private JButton[][] board;
	/**
	 * Constructor for GamePanel
	 * @param p is a List of Players that will participate in this Game
	 * @throws FileNotFoundException is thrown when cannot find the filename 
	 */
	public GamePanel(List<Player> p) throws FileNotFoundException {
		this.currentTile = null;
		this.move = new ArrayList<Tile>();
		//setting up dictionary
		Scanner scanner = new Scanner(new FileInputStream("words"), "UTF-8");
		List<String> dictionary = new ArrayList<String>();
		while (scanner.hasNext()) {
			dictionary.add(scanner.next());
		}
		scanner.close();
		g = new Game(dictionary, p);
		this.instructions = "Click a Tile you want to play, then click the Square you would like to move it to."
				+ "\n"+ "Tiles left in the bag: ";

		this.setLayout(new BorderLayout());

		//setup JTextArea that will write which player is the current player, any error messages,
		//and the winner
		this.top = new JTextArea();
		this.changeDefaultHeader();
		top.setEditable(false);
		top.setLineWrap(true);
		top.setWrapStyleWord(true);
		this.add(top, BorderLayout.NORTH);

		//setup board squares
		this.board = this.makeInitialBoard();
		boardPanel = new JPanel(new GridLayout(g.getBoard().getDimensions(), 
				g.getBoard().getDimensions()));
		for(JButton[] bs : this.board) {
			for(JButton b : bs) {
				boardPanel.add(b);
			}
		}
		this.add(boardPanel, BorderLayout.CENTER);

		//first Player's tiles
		this.tilePanel = new JPanel(new GridLayout(g.getNumTilesPerPlayer(),1));
		this.tilePanel = this.getTiles(g.getCurrentPlayer());
		this.add(tilePanel, BorderLayout.EAST);

		this.specialPanel = new JPanel(new GridLayout(g.getNumTilesPerPlayer(),1));
		this.buttonPanel = new JPanel(new GridLayout(1,3));
		//player buys special tiles
		JButton buy = new JButton("Buy Tiles");
		buy.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				drawSpecialTiles();
			}
		});
		buttonPanel.add(buy);

		JButton drawTiles = new JButton("Draw Tiles");
		drawTiles.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				redrawTiles();
			}
		});
		buttonPanel.add(drawTiles);

		//when the player is finished choosing its Tiles for the Move, hit the play button to validate the move
		JButton play = new JButton("Play");
		play.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(g.validMove(new Move(move))) {
					//valid move
					changeDefaultHeader(); //remove error message
					if(move.size() > 0) {
						g.makeMove(new Move(move));
					}
					//place Tiles on the Board
					redrawBoard();
				}
				else {
					//invalid move
					top.setText(INVALIDMOVE);
					currentTile = null; //reset and prepare for redo move
				}
				move.clear();
			}
		});
		buttonPanel.add(play);
		this.add(buttonPanel, BorderLayout.SOUTH);
		this.setVisible(true);
	}
	/**
	 * Make the initial board of Squares
	 * @return a two-dimensional array of JTextArea representing the board of Squares
	 */
	private JButton[][] makeInitialBoard() {
		int dimensions = g.getBoard().getDimensions();
		JButton[][] b = new JButton[dimensions][dimensions];
		for(int i = 0; i < dimensions; i++) {
			for(int j = 0; j < dimensions; j++) {
				Square temp = g.getBoard().getSquare(i, j);
				String label = temp.getLabel();
				b[i][j] = new JButton(label);
				b[i][j].setBackground(temp.getColor());
				b[i][j].setContentAreaFilled(false);
				b[i][j].setOpaque(true);
				final int finali = i;
				final int finalj = j;
				b[i][j].addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						squareSelected(finali,finalj);
					}
				});
			}
		}
		return b;
	}
	/**
	 * Get a JPanel with a List of JButtons, representing the current Player's Tiles
	 * @param player is a Player object representing the current Player whose Tiles to display
	 * @return a JPanel with a List of JButtons
	 */
	private JPanel getTiles(Player player) {
		JPanel tilePanel = new JPanel(new GridLayout(g.getNumTilesPerPlayer(),1));
		JButton[] buttons = new JButton[g.getNumTilesPerPlayer()];
		for(int i = 0; i < buttons.length; i++) {
			buttons[i] = new JButton();
			tilePanel.add(buttons[i]);
		}
		for(int i = 0; i < player.getTiles().size(); i++) {
			final Tile temp = player.getTiles().get(i);
			buttons[i].setText(temp.getLetter() + "\n" + Integer.toString(temp.getValue()));
			buttons[i].setForeground(temp.getColor());
			buttons[i].addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					currentTile = temp;
				}
			});
		}
		return tilePanel;
	}
	/**
	 * After a Tile is clicked on the board and a Square is selected, set the Tile's coordinates to
	 * those of the Square.
	 */
	private void squareSelected(int r, int c) {
		if(this.currentTile == null) {
			//need to select a Tile before a Square
			this.top.setText(SELECTTILE);
		}
		else {
			this.changeDefaultHeader(); //remove error message
			this.currentTile.setCoordinates(r, c);
			this.move.add(currentTile);
			this.currentTile = null; //reset and prepare for next Tile to move
		}
	}
	/**
	 * Redraw Board after Player makes a Move
	 * @param move represents the move that the Player just made
	 */
	private void redrawBoard() {
		nextPlayer();

		Move tempmove = new Move(this.move);
		for(JButton[] jbs : this.board) {
			for(JButton jb : jbs) {
				this.boardPanel.remove(jb);
			}
		}
		for(Tile t : tempmove.getTiles()) {
			this.boardPanel.remove(this.board[t.getRow()][t.getColumn()]);
			this.board[t.getRow()][t.getColumn()].setText(t.getLetter()+"\n"+t.getValue());
		}
		//correctly color the Tiles according to the current Player
		for(int i = 0; i < g.getBoard().getDimensions(); i++) {
			for(int j= 0; j < g.getBoard().getDimensions(); j++) {
				Tile t = g.getBoard().getSquare(i, j).getTile();
				if(t==null)
					continue;
				else {
					if(t.isVisible(g.getCurrentPlayer())) {
						this.board[t.getRow()][t.getColumn()].setForeground(t.getColor());
					}
					else {
						this.board[t.getRow()][t.getColumn()].setForeground(Color.BLACK);	
					}
				}
			}
		}
		for(JButton[] jbs : this.board) {
			for(JButton jb : jbs) {
				this.boardPanel.add(jb);
			}
		}
		this.boardPanel.revalidate();
		this.boardPanel.repaint();

		//prepare for next player
		this.move.clear();
		this.revalidate();
		this.repaint();
	}
	/**
	 * Change the text in the Game Panel
	 */
	private void changeDefaultHeader() {
		this.top.setText("Current player: " +g.getCurrentPlayer().getName() + "\n"+
				"Score: "+Integer.toString(g.getCurrentPlayer().getScore())+"\n"
				+instructions+Integer.toString(g.getTileBag()));
	}
	/**
	 * Change Players graphically
	 */
	private void nextPlayer() {
		this.remove(this.tilePanel);
		g.incrementPlayer();
		changeDefaultHeader();
		this.tilePanel = this.getTiles(g.getCurrentPlayer());
		this.add(tilePanel, BorderLayout.EAST);
		this.revalidate();
		this.repaint();
	}
	/**
	 * Draw new Tiles for the current Player
	 */
	private void redrawTiles() {
		Player current = g.getCurrentPlayer();
		this.remove(tilePanel);
		g.drawTiles(current);
		tilePanel=getTiles(current);
		changeDefaultHeader();
		this.add(tilePanel, BorderLayout.EAST);
	}
	/**
	 * When a Player purchases Tiles, it can select from 5 Tiles that will be drawn where their hand of Tiles is normally drawn.
	 */
	private void drawSpecialTiles() {
		List<SpecialTile> special = g.getSpecialTiles();
		this.specialPanel.removeAll();
		remove(tilePanel);
		JButton[] buttons = new JButton[g.getNumTilesPerPlayer()];
		for(int i = 0; i < g.getNumTilesPerPlayer(); i++) {
			buttons[i] = new JButton();
		}
		for(int i = 0; i < special.size(); i++) {
			final SpecialTile temp = special.get(i);
			buttons[i].setText(temp.getLetter() + "\n" + Integer.toString(temp.getValue()));
			buttons[i].setForeground(temp.getColor());
			buttons[i].addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					boolean b = g.purchase(temp);
					if(b) {
						remove(specialPanel);
						tilePanel = getTiles(g.getCurrentPlayer());
						changeDefaultHeader();
						add(tilePanel, BorderLayout.EAST);
						revalidate();
						repaint();
					}
					else {
						top.setText(CANNOTAFFORD);
						revalidate();
						repaint();
					}
				}
			});
		}
		buttons[g.getNumTilesPerPlayer()-1].setText("Back");
		buttons[g.getNumTilesPerPlayer()-1].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				remove(specialPanel);
				tilePanel = getTiles(g.getCurrentPlayer());
				changeDefaultHeader();
				add(tilePanel, BorderLayout.EAST);
				revalidate();
				repaint();
			}
		});
		specialPanel = new JPanel(new GridLayout(g.getNumTilesPerPlayer(),1));
		for(JButton b : buttons) {
			this.specialPanel.add(b);
		}
		this.add(this.specialPanel, BorderLayout.EAST);
		revalidate();
		repaint();
	}
}