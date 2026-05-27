# Security Considerations

## Public Repository Controls

- Do not commit AWS IoT certificates, private keys, API Gateway URLs, live passwords, device identifiers, or personal emails.
- Keep `config.js` local and ignored by Git.
- Rotate any certificates or API endpoints that were previously exposed outside a private environment.

## Deployment Controls

- Use HTTPS for all dashboard-to-API traffic.
- Protect API Gateway endpoints with appropriate authorization instead of relying on frontend-only checks.
- Apply least-privilege IAM policies to Lambda, IoT, and storage resources.
- Rotate AWS IoT device certificates and disable certificates that are no longer used.
- Add request validation, CORS restrictions, throttling, logging, and alarms on public-facing APIs.
- Store secrets in AWS-managed secret stores or deployment environment variables, not in source code.

## Frontend Authentication Note

The browser password in this public demo is only a convenience gate for demonstration. It is not production-grade authentication because client-side code can be inspected by users.
