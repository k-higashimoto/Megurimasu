package lib.tableView;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Point {
    private SimpleStringProperty itemOfPoint;
    private SimpleIntegerProperty teamAPoint;
    private SimpleIntegerProperty teamBPoint;

    public Point(String itemOfPoint, int teamAPoint, int teamBPoint) {
        this.itemOfPoint = new SimpleStringProperty(itemOfPoint);
        this.teamAPoint = new SimpleIntegerProperty(teamAPoint);
        this.teamBPoint = new SimpleIntegerProperty(teamBPoint);
    }

    public StringProperty itemOfPointProperty() {
        return itemOfPoint;
    }

    public IntegerProperty teamAPointProperty() {
        return teamAPoint;
    }

    public IntegerProperty teamBPointProperty() {
        return teamBPoint;
    }
}
