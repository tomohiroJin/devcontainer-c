#!/usr/bin/env python3
"""Expose the unfiltered Trivy findings in logs and the GitHub job summary."""
import hashlib
import json
import os
from collections import Counter
from pathlib import Path
import sys

report_path = Path(sys.argv[1])
raw_report = report_path.read_bytes()
report = json.loads(raw_report)
findings = [
    finding
    for result in report["Results"]
    for finding in result.get("Vulnerabilities", [])
]
counts = Counter(finding["Severity"] for finding in findings)
fixable_high = sum(
    finding["Severity"] in {"HIGH", "CRITICAL"} and bool(finding.get("FixedVersion"))
    for finding in findings
)
lines = [
    "## Unfiltered Trivy vulnerability findings",
    "",
    "Counts include unfixed findings and repeated CVEs across packages.",
    "",
    "| Severity | Package findings |",
    "| --- | ---: |",
]
lines.extend(
    f"| {severity} | {counts[severity]} |"
    for severity in ["CRITICAL", "HIGH", "MEDIUM", "LOW", "UNKNOWN"]
)
lines.extend(
    [
        "",
        f"Total package findings: {len(findings)}",
        f"Unique vulnerability IDs: {len({finding['VulnerabilityID'] for finding in findings})}",
        f"Fixable HIGH/CRITICAL package findings: {fixable_high}",
        f"Image ID: `{report.get('Metadata', {}).get('ImageID', 'unavailable')}`",
        f"Report SHA256: `{hashlib.sha256(raw_report).hexdigest()}`",
        "",
        "The raw trivy.json, package list and image metadata are in the security-evidence artifact.",
        "The separate security gate fails on fixable HIGH/CRITICAL findings.",
    ]
)
summary = "\n".join(lines) + "\n"
print(summary, end="")
if summary_path := os.environ.get("GITHUB_STEP_SUMMARY"):
    with open(summary_path, "a", encoding="utf-8") as stream:
        stream.write(summary)
