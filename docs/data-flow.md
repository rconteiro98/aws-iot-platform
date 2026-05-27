# Data Flow

## Sensor Status

1. Arduino-connected sensors produce dry/wet/drying readings.
2. Backend services expose the latest state through a status API.
3. The dashboard polls sensor status and updates the floor-plan state.
4. Wet events open an operator workflow and add an audit entry.

## RFID Response

1. The dashboard polls for recent RFID tap events.
2. RFID IDs are mapped to staff assignments in browser local storage.
3. A matching tap can move a sensor into a handling state.
4. The event audit log records the response action.

## Device Configuration

1. The dashboard requests the current configuration for a selected Arduino device.
2. Operators toggle individual sensors or update thresholds.
3. The dashboard sends update requests to the backend.
4. A push action sends the selected configuration to the device-side workflow.

## Actuator Control

1. The dashboard reads the current actuator state from the actuator API.
2. Operators toggle system LEDs from the UI.
3. The dashboard sends a command request and rolls back the UI if the request fails.
