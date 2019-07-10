package lib.tableView;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Position {
    private SimpleStringProperty itemOfPosition;
    private SimpleIntegerProperty teamAPosition;
    private SimpleIntegerProperty teamBPosition;

    public Position(String item, int teamAPosition, int teamBPosition) {
        this.itemOfPosition = new SimpleStringProperty(item);
        this.teamAPosition = new SimpleIntegerProperty(teamAPosition);
        this.teamBPosition = new SimpleIntegerProperty(teamBPosition);
    }

    public StringProperty itemOfPositionProperty() {
        return itemOfPosition;
    }

    public IntegerProperty teamAPositionProperty() {
        return teamAPosition;
    }

    public IntegerProperty teamBPositionProperty() {
        return teamBPosition;
    }
}
