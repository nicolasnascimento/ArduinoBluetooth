#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_

// A Traffic Light Controller
namespace TrafficLight {

  // The state in which you the Traffic Light can be in
  enum State{
    open, closing, closed, off
  };

  // The colors in which the Traffic Light can assume
  enum Color {
    green, yellow, red
  };

  enum Mode {
    normal, emergency
  };

  class ColorUpdater {
  private:
    // MARK: - Private Properties

    // The pins used to for updating the colors
    int _redPin, _yellowPin, _greenPin;

    // The current color the updater is presenting
    Color _currentColor;

    // MARK: - Private Methods

    void _switchToColorUsingPin(const Color color, const int pin) {
      _currentColor = color;
      // Switch Off All Pins
      switchOff();

      // Switch On the required pin
      digitalWrite(pin, HIGH);
    }

  public:
    ColorUpdater(const int redPin = 0, const int yellowPin = 0, const int greenPin = 0) {
      // Set Variables
      _redPin = redPin;
      _yellowPin = yellowPin;
      _greenPin = greenPin;

      // Default Color
      _currentColor = yellow;

      // Set Pins as outputs
      pinMode(_redPin, OUTPUT);
      pinMode(_yellowPin, OUTPUT);
      pinMode(_greenPin, OUTPUT);
    }

    void switchToRed() { 
      _switchToColorUsingPin(red, _redPin);
    }
    void switchToYellow() { 
      _switchToColorUsingPin(yellow, _yellowPin);
    }
    void switchToGreen() { 
      _switchToColorUsingPin(green, _greenPin);
    }
    void switchOff() {
      digitalWrite(_redPin, LOW);
      digitalWrite(_yellowPin, LOW);
      digitalWrite(_greenPin, LOW);
    }
  };


  // Forward Declaration
  class StateUpdater;
  
  class StateUpdaterDelegate {
  public: 
    virtual void stateUpdaterDidUpdateColor(const StateUpdater& updater, State newState) = 0;
  };

  class StateUpdater {
  private:
    // The current state of the Updater
    State _currentState = open;

  public:
    // The delegate which will respond to State updates
    StateUpdaterDelegate* _delegate;
 
    StateUpdater() {
      _delegate = NULL;
      _currentState = off;
    }

    State currentState() const {
      return _currentState;
    }
    void updateStateTo(State newState) {
      _currentState = newState;
     if( _delegate != NULL ) {
      _delegate->stateUpdaterDidUpdateColor(*this, _currentState);
     }
    }
  };

  // The manager of the Traffic Light System
  class Manager: public StateUpdaterDelegate {
  private:

    StateUpdater _stateUpdater;
    ColorUpdater _colorUpdater;

    Mode _mode;
  public:
    // MARK: - Static

    static const int redPin = 7;
    static const int yellowPin = 6;
    static const int greenPin = 5;

    static const int shortDelay = 1000;
    static const int mediumDelay = 2000;
    static const int longDelay = 3000;
    static const int veryLongDelay = 4000;

    // MARK: - Public

    Manager() {
      _colorUpdater = ColorUpdater(Manager::redPin, Manager::yellowPin, Manager::greenPin);
      _stateUpdater = StateUpdater();
      _stateUpdater._delegate = this;
      _mode = normal;
    }

    // Returns the waiting for the current step
    int step() {

      if( _mode == normal ) {
        switch(_stateUpdater.currentState()) {
          case open:
            _stateUpdater.updateStateTo(closing);
            return Manager::mediumDelay;
          case closing:
            _stateUpdater.updateStateTo(closed);
            return Manager::veryLongDelay;
          case closed:
            _stateUpdater.updateStateTo(open);
            return Manager::veryLongDelay;
          case off:
            _stateUpdater.updateStateTo(open);
            return Manager::shortDelay;
        }
      } else {
        switch(_stateUpdater.currentState()) {
          case off:
            _stateUpdater.updateStateTo(closing);
            return Manager::mediumDelay;
          default:
            _stateUpdater.updateStateTo(off);
            return Manager::mediumDelay;
        }
      }
      return Manager::shortDelay;
    }
    void switchMode() {
      switch(_mode) {
        case normal: _mode = emergency;
          break;
        case emergency: _mode = normal;
          break;
      }
    }

    // MARK: - ColorUpdater Delegate

    void stateUpdaterDidUpdateColor(const StateUpdater& updater, State newState) {
      switch(updater.currentState()) {
        case open:
          _colorUpdater.switchToGreen();
          break;
        case closing:
          _colorUpdater.switchToYellow();
          break;
        case closed:
          _colorUpdater.switchToRed();
          break;
        case off:
          _colorUpdater.switchOff();
          break;
      }
    }
  };
};

#endif // _TRAFFIC_LIGHT_H_
