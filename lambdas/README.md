# Lambda Functions

This folder contains public-safe AWS Lambda source code used by the SensorWatch IoT platform.

## `iot_ingest_lambda.py`

Ingests AWS IoT / MQTT-style events and writes them to PostgreSQL-backed tables for:

- water-level sensor history
- latest sensor state snapshots
- RFID scan events
- device heartbeat events

The function expects database settings and table names through environment variables. No credentials, endpoints, ARNs, or private infrastructure values should be committed to this repository.

Required environment variables:

```text
DB_HOST
DB_NAME
DB_USER
DB_PASS
```

Optional environment variables:

```text
DB_PORT=5432
HISTORY_TABLE=waterlevel_readings
SENSORSTATE_TABLE=sensorstate
RFID_TABLE=rfid_scans
HEARTBEAT_TABLE=device_heartbeats
```

Deployment notes:

- Package `psycopg2` with the Lambda deployment artifact or provide it through a compatible Lambda layer.
- Keep database credentials in Lambda environment variables or AWS-managed secret storage.
- Restrict database network access to approved Lambda/VPC paths.
- Rotate credentials and certificates after testing or public demonstrations.
