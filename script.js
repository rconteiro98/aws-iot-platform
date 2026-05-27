function toggleSensor(sensorId) {
    const card = document.getElementById(`sensor-${sensorId}`);
    const indicator = card.querySelector('.indicator');
    const reading = card.querySelector('.reading');
    const button = card.querySelector('.simulate-btn');

    if (indicator.classList.contains('green')) {
        // Switch to Wet state
        indicator.classList.remove('green');
        indicator.classList.add('red');
        reading.textContent = 'Wet Alert!';
        reading.classList.add('alert');
        button.textContent = 'Simulate Dry';
    } else {
        // Switch to Dry state
        indicator.classList.remove('red');
        indicator.classList.add('green');
        reading.textContent = 'Dry';
        reading.classList.remove('alert');
        button.textContent = 'Simulate Wet';
    }
}
